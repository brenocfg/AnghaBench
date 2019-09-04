#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  unsigned int u32 ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GMBUS0 ; 
 int /*<<< orphan*/  GMBUS1 ; 
 int /*<<< orphan*/  GMBUS3 ; 
 unsigned int GMBUS_BYTE_CNT_OVERRIDE ; 
 unsigned int GMBUS_BYTE_COUNT_SHIFT ; 
 unsigned int GMBUS_CYCLE_WAIT ; 
 int /*<<< orphan*/  GMBUS_HW_RDY ; 
 int /*<<< orphan*/  GMBUS_HW_RDY_EN ; 
 unsigned short GMBUS_SLAVE_ADDR_SHIFT ; 
 unsigned int GMBUS_SLAVE_READ ; 
 unsigned int GMBUS_SW_RDY ; 
 unsigned int I915_READ_FW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE_FW (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int gmbus_max_xfer_size (struct drm_i915_private*) ; 
 int gmbus_wait (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
gmbus_xfer_read_chunk(struct drm_i915_private *dev_priv,
		      unsigned short addr, u8 *buf, unsigned int len,
		      u32 gmbus0_reg, u32 gmbus1_index)
{
	unsigned int size = len;
	bool burst_read = len > gmbus_max_xfer_size(dev_priv);
	bool extra_byte_added = false;

	if (burst_read) {
		/*
		 * As per HW Spec, for 512Bytes need to read extra Byte and
		 * Ignore the extra byte read.
		 */
		if (len == 512) {
			extra_byte_added = true;
			len++;
		}
		size = len % 256 + 256;
		I915_WRITE_FW(GMBUS0, gmbus0_reg | GMBUS_BYTE_CNT_OVERRIDE);
	}

	I915_WRITE_FW(GMBUS1,
		      gmbus1_index |
		      GMBUS_CYCLE_WAIT |
		      (size << GMBUS_BYTE_COUNT_SHIFT) |
		      (addr << GMBUS_SLAVE_ADDR_SHIFT) |
		      GMBUS_SLAVE_READ | GMBUS_SW_RDY);
	while (len) {
		int ret;
		u32 val, loop = 0;

		ret = gmbus_wait(dev_priv, GMBUS_HW_RDY, GMBUS_HW_RDY_EN);
		if (ret)
			return ret;

		val = I915_READ_FW(GMBUS3);
		do {
			if (extra_byte_added && len == 1)
				break;

			*buf++ = val & 0xff;
			val >>= 8;
		} while (--len && ++loop < 4);

		if (burst_read && len == size - 4)
			/* Reset the override bit */
			I915_WRITE_FW(GMBUS0, gmbus0_reg);
	}

	return 0;
}