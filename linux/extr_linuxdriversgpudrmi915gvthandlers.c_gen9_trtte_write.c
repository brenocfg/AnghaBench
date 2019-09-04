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
struct intel_vgpu {int /*<<< orphan*/  id; TYPE_1__* gvt; } ;
struct drm_i915_private {int dummy; } ;
struct TYPE_2__ {struct drm_i915_private* dev_priv; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _MMIO (unsigned int) ; 
 int /*<<< orphan*/  mmio_hw_access_post (struct drm_i915_private*) ; 
 int /*<<< orphan*/  mmio_hw_access_pre (struct drm_i915_private*) ; 
 int /*<<< orphan*/  vgpu_vreg (struct intel_vgpu*,unsigned int) ; 
 int /*<<< orphan*/  write_vreg (struct intel_vgpu*,unsigned int,void*,unsigned int) ; 

__attribute__((used)) static int gen9_trtte_write(struct intel_vgpu *vgpu, unsigned int offset,
		void *p_data, unsigned int bytes)
{
	struct drm_i915_private *dev_priv = vgpu->gvt->dev_priv;
	u32 trtte = *(u32 *)p_data;

	if ((trtte & 1) && (trtte & (1 << 1)) == 0) {
		WARN(1, "VM(%d): Use physical address for TRTT!\n",
				vgpu->id);
		return -EINVAL;
	}
	write_vreg(vgpu, offset, p_data, bytes);
	/* TRTTE is not per-context */

	mmio_hw_access_pre(dev_priv);
	I915_WRITE(_MMIO(offset), vgpu_vreg(vgpu, offset));
	mmio_hw_access_post(dev_priv);

	return 0;
}