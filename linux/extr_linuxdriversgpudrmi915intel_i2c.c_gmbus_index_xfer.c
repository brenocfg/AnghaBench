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
typedef  int u32 ;
struct i2c_msg {int len; int* buf; int flags; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GMBUS5 ; 
 int GMBUS_2BYTE_INDEX_EN ; 
 int GMBUS_CYCLE_INDEX ; 
 int GMBUS_SLAVE_INDEX_SHIFT ; 
 int I2C_M_RD ; 
 int /*<<< orphan*/  I915_WRITE_FW (int /*<<< orphan*/ ,int) ; 
 int gmbus_xfer_read (struct drm_i915_private*,struct i2c_msg*,int,int) ; 
 int gmbus_xfer_write (struct drm_i915_private*,struct i2c_msg*,int) ; 

__attribute__((used)) static int
gmbus_index_xfer(struct drm_i915_private *dev_priv, struct i2c_msg *msgs,
		 u32 gmbus0_reg)
{
	u32 gmbus1_index = 0;
	u32 gmbus5 = 0;
	int ret;

	if (msgs[0].len == 2)
		gmbus5 = GMBUS_2BYTE_INDEX_EN |
			 msgs[0].buf[1] | (msgs[0].buf[0] << 8);
	if (msgs[0].len == 1)
		gmbus1_index = GMBUS_CYCLE_INDEX |
			       (msgs[0].buf[0] << GMBUS_SLAVE_INDEX_SHIFT);

	/* GMBUS5 holds 16-bit index */
	if (gmbus5)
		I915_WRITE_FW(GMBUS5, gmbus5);

	if (msgs[1].flags & I2C_M_RD)
		ret = gmbus_xfer_read(dev_priv, &msgs[1], gmbus0_reg,
				      gmbus1_index);
	else
		ret = gmbus_xfer_write(dev_priv, &msgs[1], gmbus1_index);

	/* Clear GMBUS5 after each index transfer */
	if (gmbus5)
		I915_WRITE_FW(GMBUS5, 0);

	return ret;
}