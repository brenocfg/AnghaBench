#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct intel_vgpu {TYPE_1__* gvt; } ;
struct drm_i915_private {int dummy; } ;
struct TYPE_2__ {struct drm_i915_private* dev_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _MMIO (unsigned int) ; 
 int /*<<< orphan*/  mmio_hw_access_post (struct drm_i915_private*) ; 
 int /*<<< orphan*/  mmio_hw_access_pre (struct drm_i915_private*) ; 
 int /*<<< orphan*/  write_vreg (struct intel_vgpu*,unsigned int,void*,unsigned int) ; 

__attribute__((used)) static int gen9_trtt_chicken_write(struct intel_vgpu *vgpu, unsigned int offset,
		void *p_data, unsigned int bytes)
{
	struct drm_i915_private *dev_priv = vgpu->gvt->dev_priv;
	u32 val = *(u32 *)p_data;

	if (val & 1) {
		/* unblock hw logic */
		mmio_hw_access_pre(dev_priv);
		I915_WRITE(_MMIO(offset), val);
		mmio_hw_access_post(dev_priv);
	}
	write_vreg(vgpu, offset, p_data, bytes);
	return 0;
}