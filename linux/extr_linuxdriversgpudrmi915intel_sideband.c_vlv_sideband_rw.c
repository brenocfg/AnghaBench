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
struct drm_i915_private {int /*<<< orphan*/  sb_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,char*) ; 
 int EAGAIN ; 
 int ETIMEDOUT ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int IOSF_BAR_SHIFT ; 
 int IOSF_BYTE_ENABLES_SHIFT ; 
 int IOSF_DEVFN_SHIFT ; 
 int IOSF_OPCODE_SHIFT ; 
 int IOSF_PORT_SHIFT ; 
 int /*<<< orphan*/  IOSF_SB_BUSY ; 
 int SB_CRRDDA_NP ; 
 int SB_MRD_NP ; 
 int /*<<< orphan*/  VLV_IOSF_ADDR ; 
 int /*<<< orphan*/  VLV_IOSF_DATA ; 
 int /*<<< orphan*/  VLV_IOSF_DOORBELL_REQ ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ intel_wait_for_register (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlv_sideband_rw(struct drm_i915_private *dev_priv, u32 devfn,
			   u32 port, u32 opcode, u32 addr, u32 *val)
{
	u32 cmd, be = 0xf, bar = 0;
	bool is_read = (opcode == SB_MRD_NP || opcode == SB_CRRDDA_NP);

	cmd = (devfn << IOSF_DEVFN_SHIFT) | (opcode << IOSF_OPCODE_SHIFT) |
		(port << IOSF_PORT_SHIFT) | (be << IOSF_BYTE_ENABLES_SHIFT) |
		(bar << IOSF_BAR_SHIFT);

	WARN_ON(!mutex_is_locked(&dev_priv->sb_lock));

	if (intel_wait_for_register(dev_priv,
				    VLV_IOSF_DOORBELL_REQ, IOSF_SB_BUSY, 0,
				    5)) {
		DRM_DEBUG_DRIVER("IOSF sideband idle wait (%s) timed out\n",
				 is_read ? "read" : "write");
		return -EAGAIN;
	}

	I915_WRITE(VLV_IOSF_ADDR, addr);
	I915_WRITE(VLV_IOSF_DATA, is_read ? 0 : *val);
	I915_WRITE(VLV_IOSF_DOORBELL_REQ, cmd);

	if (intel_wait_for_register(dev_priv,
				    VLV_IOSF_DOORBELL_REQ, IOSF_SB_BUSY, 0,
				    5)) {
		DRM_DEBUG_DRIVER("IOSF sideband finish wait (%s) timed out\n",
				 is_read ? "read" : "write");
		return -ETIMEDOUT;
	}

	if (is_read)
		*val = I915_READ(VLV_IOSF_DATA);

	return 0;
}