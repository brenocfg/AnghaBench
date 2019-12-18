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
typedef  int u64 ;
typedef  int u32 ;
struct intel_renderstate_rodata {unsigned int batch_items; int* batch; unsigned int* reloc; } ;
struct intel_renderstate {int batch_size; unsigned int aux_offset; unsigned int aux_size; int /*<<< orphan*/  obj; scalar_t__ batch_offset; TYPE_2__* vma; struct intel_renderstate_rodata* rodata; } ;
struct drm_i915_private {int dummy; } ;
struct TYPE_3__ {int start; } ;
struct TYPE_4__ {TYPE_1__ node; } ;

/* Variables and functions */
 unsigned int ALIGN (unsigned int,int) ; 
 unsigned int CACHELINE_DWORDS ; 
 int /*<<< orphan*/  DRM_ERROR (char*,unsigned int) ; 
 int EINVAL ; 
 int GEN9_MEDIA_POOL_ENABLE ; 
 int GEN9_MEDIA_POOL_STATE ; 
 scalar_t__ HAS_64BIT_RELOC (struct drm_i915_private*) ; 
 scalar_t__ HAS_POOLED_EU (struct drm_i915_private*) ; 
 int MI_BATCH_BUFFER_END ; 
 int MI_NOOP ; 
 int /*<<< orphan*/  OUT_BATCH (int*,unsigned int,int) ; 
 int /*<<< orphan*/  drm_clflush_virt_range (int*,unsigned int) ; 
 int /*<<< orphan*/  i915_gem_object_finish_access (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_object_get_dirty_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i915_gem_object_prepare_write (int /*<<< orphan*/ ,unsigned int*) ; 
 scalar_t__ i915_ggtt_offset (TYPE_2__*) ; 
 int* kmap_atomic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (int*) ; 
 int lower_32_bits (int) ; 
 int upper_32_bits (int) ; 

__attribute__((used)) static int render_state_setup(struct intel_renderstate *so,
			      struct drm_i915_private *i915)
{
	const struct intel_renderstate_rodata *rodata = so->rodata;
	unsigned int i = 0, reloc_index = 0;
	unsigned int needs_clflush;
	u32 *d;
	int ret;

	ret = i915_gem_object_prepare_write(so->obj, &needs_clflush);
	if (ret)
		return ret;

	d = kmap_atomic(i915_gem_object_get_dirty_page(so->obj, 0));

	while (i < rodata->batch_items) {
		u32 s = rodata->batch[i];

		if (i * 4  == rodata->reloc[reloc_index]) {
			u64 r = s + so->vma->node.start;
			s = lower_32_bits(r);
			if (HAS_64BIT_RELOC(i915)) {
				if (i + 1 >= rodata->batch_items ||
				    rodata->batch[i + 1] != 0)
					goto err;

				d[i++] = s;
				s = upper_32_bits(r);
			}

			reloc_index++;
		}

		d[i++] = s;
	}

	if (rodata->reloc[reloc_index] != -1) {
		DRM_ERROR("only %d relocs resolved\n", reloc_index);
		goto err;
	}

	so->batch_offset = i915_ggtt_offset(so->vma);
	so->batch_size = rodata->batch_items * sizeof(u32);

	while (i % CACHELINE_DWORDS)
		OUT_BATCH(d, i, MI_NOOP);

	so->aux_offset = i * sizeof(u32);

	if (HAS_POOLED_EU(i915)) {
		/*
		 * We always program 3x6 pool config but depending upon which
		 * subslice is disabled HW drops down to appropriate config
		 * shown below.
		 *
		 * In the below table 2x6 config always refers to
		 * fused-down version, native 2x6 is not available and can
		 * be ignored
		 *
		 * SNo  subslices config                eu pool configuration
		 * -----------------------------------------------------------
		 * 1    3 subslices enabled (3x6)  -    0x00777000  (9+9)
		 * 2    ss0 disabled (2x6)         -    0x00777000  (3+9)
		 * 3    ss1 disabled (2x6)         -    0x00770000  (6+6)
		 * 4    ss2 disabled (2x6)         -    0x00007000  (9+3)
		 */
		u32 eu_pool_config = 0x00777000;

		OUT_BATCH(d, i, GEN9_MEDIA_POOL_STATE);
		OUT_BATCH(d, i, GEN9_MEDIA_POOL_ENABLE);
		OUT_BATCH(d, i, eu_pool_config);
		OUT_BATCH(d, i, 0);
		OUT_BATCH(d, i, 0);
		OUT_BATCH(d, i, 0);
	}

	OUT_BATCH(d, i, MI_BATCH_BUFFER_END);
	so->aux_size = i * sizeof(u32) - so->aux_offset;
	so->aux_offset += so->batch_offset;
	/*
	 * Since we are sending length, we need to strictly conform to
	 * all requirements. For Gen2 this must be a multiple of 8.
	 */
	so->aux_size = ALIGN(so->aux_size, 8);

	if (needs_clflush)
		drm_clflush_virt_range(d, i * sizeof(u32));
	kunmap_atomic(d);

	ret = 0;
out:
	i915_gem_object_finish_access(so->obj);
	return ret;

err:
	kunmap_atomic(d);
	ret = -EINVAL;
	goto out;
}