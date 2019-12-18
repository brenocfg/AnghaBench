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
typedef  scalar_t__ u32 ;
struct intel_timeline_cacheline {int /*<<< orphan*/  vaddr; TYPE_1__* hwsp; } ;
struct intel_timeline {int /*<<< orphan*/  mutex; scalar_t__ hwsp_offset; struct intel_timeline_cacheline* hwsp_cacheline; } ;
struct i915_request {struct intel_timeline* timeline; struct intel_timeline_cacheline* hwsp_cacheline; } ;
struct TYPE_2__ {int /*<<< orphan*/  vma; } ;

/* Variables and functions */
 int /*<<< orphan*/  CACHELINE_BITS ; 
 int CACHELINE_BYTES ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  SINGLE_DEPTH_NESTING ; 
 int cacheline_ref (struct intel_timeline_cacheline*,struct i915_request*) ; 
 scalar_t__ i915_ggtt_offset (int /*<<< orphan*/ ) ; 
 int i915_request_completed (struct i915_request*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int ptr_unmask_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int intel_timeline_read_hwsp(struct i915_request *from,
			     struct i915_request *to,
			     u32 *hwsp)
{
	struct intel_timeline_cacheline *cl = from->hwsp_cacheline;
	struct intel_timeline *tl = from->timeline;
	int err;

	GEM_BUG_ON(to->timeline == tl);

	mutex_lock_nested(&tl->mutex, SINGLE_DEPTH_NESTING);
	err = i915_request_completed(from);
	if (!err)
		err = cacheline_ref(cl, to);
	if (!err) {
		if (likely(cl == tl->hwsp_cacheline)) {
			*hwsp = tl->hwsp_offset;
		} else { /* across a seqno wrap, recover the original offset */
			*hwsp = i915_ggtt_offset(cl->hwsp->vma) +
				ptr_unmask_bits(cl->vaddr, CACHELINE_BITS) *
				CACHELINE_BYTES;
		}
	}
	mutex_unlock(&tl->mutex);

	return err;
}