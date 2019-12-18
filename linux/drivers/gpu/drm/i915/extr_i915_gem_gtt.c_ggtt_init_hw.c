#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  start; } ;
struct TYPE_6__ {int /*<<< orphan*/  color_adjust; } ;
struct TYPE_9__ {int is_ggtt; int /*<<< orphan*/  (* cleanup ) (TYPE_4__*) ;TYPE_1__ mm; int /*<<< orphan*/  has_read_only; struct drm_i915_private* i915; } ;
struct i915_ggtt {int /*<<< orphan*/  mappable_end; TYPE_2__ gmadr; int /*<<< orphan*/  mtrr; TYPE_4__ vm; int /*<<< orphan*/  iomap; } ;
struct TYPE_8__ {int /*<<< orphan*/  struct_mutex; } ;
struct drm_i915_private {TYPE_3__ drm; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  HAS_LLC (struct drm_i915_private*) ; 
 int /*<<< orphan*/  HAS_PPGTT (struct drm_i915_private*) ; 
 int /*<<< orphan*/  IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  VM_CLASS_GGTT ; 
 int /*<<< orphan*/  arch_phys_wc_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_address_space_init (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_ggtt_init_fences (struct i915_ggtt*) ; 
 int /*<<< orphan*/  i915_gtt_color_adjust ; 
 int /*<<< orphan*/  io_mapping_init_wc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 

__attribute__((used)) static int ggtt_init_hw(struct i915_ggtt *ggtt)
{
	struct drm_i915_private *i915 = ggtt->vm.i915;
	int ret = 0;

	mutex_lock(&i915->drm.struct_mutex);

	i915_address_space_init(&ggtt->vm, VM_CLASS_GGTT);

	ggtt->vm.is_ggtt = true;

	/* Only VLV supports read-only GGTT mappings */
	ggtt->vm.has_read_only = IS_VALLEYVIEW(i915);

	if (!HAS_LLC(i915) && !HAS_PPGTT(i915))
		ggtt->vm.mm.color_adjust = i915_gtt_color_adjust;

	if (!io_mapping_init_wc(&ggtt->iomap,
				ggtt->gmadr.start,
				ggtt->mappable_end)) {
		ggtt->vm.cleanup(&ggtt->vm);
		ret = -EIO;
		goto out;
	}

	ggtt->mtrr = arch_phys_wc_add(ggtt->gmadr.start, ggtt->mappable_end);

	i915_ggtt_init_fences(ggtt);

out:
	mutex_unlock(&i915->drm.struct_mutex);

	return ret;
}