#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  low_gm_node; } ;
struct intel_vgpu {TYPE_1__ gm; int /*<<< orphan*/  id; struct intel_gvt* gvt; } ;
struct intel_gvt {struct drm_i915_private* dev_priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  struct_mutex; } ;
struct drm_i915_private {TYPE_2__ drm; } ;

/* Variables and functions */
 int alloc_gm (struct intel_vgpu*,int) ; 
 int /*<<< orphan*/  drm_mm_remove_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gvt_dbg_core (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vgpu_aperture_offset (struct intel_vgpu*) ; 
 int /*<<< orphan*/  vgpu_aperture_sz (struct intel_vgpu*) ; 
 int /*<<< orphan*/  vgpu_hidden_offset (struct intel_vgpu*) ; 
 int /*<<< orphan*/  vgpu_hidden_sz (struct intel_vgpu*) ; 

__attribute__((used)) static int alloc_vgpu_gm(struct intel_vgpu *vgpu)
{
	struct intel_gvt *gvt = vgpu->gvt;
	struct drm_i915_private *dev_priv = gvt->dev_priv;
	int ret;

	ret = alloc_gm(vgpu, false);
	if (ret)
		return ret;

	ret = alloc_gm(vgpu, true);
	if (ret)
		goto out_free_aperture;

	gvt_dbg_core("vgpu%d: alloc low GM start %llx size %llx\n", vgpu->id,
		     vgpu_aperture_offset(vgpu), vgpu_aperture_sz(vgpu));

	gvt_dbg_core("vgpu%d: alloc high GM start %llx size %llx\n", vgpu->id,
		     vgpu_hidden_offset(vgpu), vgpu_hidden_sz(vgpu));

	return 0;
out_free_aperture:
	mutex_lock(&dev_priv->drm.struct_mutex);
	drm_mm_remove_node(&vgpu->gm.low_gm_node);
	mutex_unlock(&dev_priv->drm.struct_mutex);
	return ret;
}