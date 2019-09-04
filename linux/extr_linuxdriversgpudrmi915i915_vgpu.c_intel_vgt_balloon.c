#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned long total; } ;
struct i915_ggtt {unsigned long mappable_end; TYPE_1__ vm; } ;
struct drm_i915_private {struct i915_ggtt ggtt; } ;
struct TYPE_8__ {int /*<<< orphan*/  size; int /*<<< orphan*/  base; } ;
struct TYPE_7__ {int /*<<< orphan*/  size; int /*<<< orphan*/  base; } ;
struct TYPE_10__ {TYPE_3__ nonmappable_gmadr; TYPE_2__ mappable_gmadr; } ;
struct TYPE_9__ {int /*<<< orphan*/ * space; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  DRM_INFO (char*,...) ; 
 int EINVAL ; 
 unsigned long I915_READ (int /*<<< orphan*/ ) ; 
 TYPE_5__ avail_rs ; 
 TYPE_4__ bl_info ; 
 int /*<<< orphan*/  intel_vgpu_active (struct drm_i915_private*) ; 
 int vgt_balloon_space (struct i915_ggtt*,int /*<<< orphan*/ *,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  vgt_deballoon_space (struct i915_ggtt*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vgtif_reg (int /*<<< orphan*/ ) ; 

int intel_vgt_balloon(struct drm_i915_private *dev_priv)
{
	struct i915_ggtt *ggtt = &dev_priv->ggtt;
	unsigned long ggtt_end = ggtt->vm.total;

	unsigned long mappable_base, mappable_size, mappable_end;
	unsigned long unmappable_base, unmappable_size, unmappable_end;
	int ret;

	if (!intel_vgpu_active(dev_priv))
		return 0;

	mappable_base = I915_READ(vgtif_reg(avail_rs.mappable_gmadr.base));
	mappable_size = I915_READ(vgtif_reg(avail_rs.mappable_gmadr.size));
	unmappable_base = I915_READ(vgtif_reg(avail_rs.nonmappable_gmadr.base));
	unmappable_size = I915_READ(vgtif_reg(avail_rs.nonmappable_gmadr.size));

	mappable_end = mappable_base + mappable_size;
	unmappable_end = unmappable_base + unmappable_size;

	DRM_INFO("VGT ballooning configuration:\n");
	DRM_INFO("Mappable graphic memory: base 0x%lx size %ldKiB\n",
		 mappable_base, mappable_size / 1024);
	DRM_INFO("Unmappable graphic memory: base 0x%lx size %ldKiB\n",
		 unmappable_base, unmappable_size / 1024);

	if (mappable_end > ggtt->mappable_end ||
	    unmappable_base < ggtt->mappable_end ||
	    unmappable_end > ggtt_end) {
		DRM_ERROR("Invalid ballooning configuration!\n");
		return -EINVAL;
	}

	/* Unmappable graphic memory ballooning */
	if (unmappable_base > ggtt->mappable_end) {
		ret = vgt_balloon_space(ggtt, &bl_info.space[2],
					ggtt->mappable_end, unmappable_base);

		if (ret)
			goto err;
	}

	if (unmappable_end < ggtt_end) {
		ret = vgt_balloon_space(ggtt, &bl_info.space[3],
					unmappable_end, ggtt_end);
		if (ret)
			goto err_upon_mappable;
	}

	/* Mappable graphic memory ballooning */
	if (mappable_base) {
		ret = vgt_balloon_space(ggtt, &bl_info.space[0],
					0, mappable_base);

		if (ret)
			goto err_upon_unmappable;
	}

	if (mappable_end < ggtt->mappable_end) {
		ret = vgt_balloon_space(ggtt, &bl_info.space[1],
					mappable_end, ggtt->mappable_end);

		if (ret)
			goto err_below_mappable;
	}

	DRM_INFO("VGT balloon successfully\n");
	return 0;

err_below_mappable:
	vgt_deballoon_space(ggtt, &bl_info.space[0]);
err_upon_unmappable:
	vgt_deballoon_space(ggtt, &bl_info.space[3]);
err_upon_mappable:
	vgt_deballoon_space(ggtt, &bl_info.space[2]);
err:
	DRM_ERROR("VGT balloon fail\n");
	return ret;
}