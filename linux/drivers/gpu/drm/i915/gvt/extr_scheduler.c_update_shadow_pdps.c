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
struct page {int dummy; } ;
struct intel_vgpu_workload {TYPE_5__* shadow_mm; TYPE_4__* req; } ;
struct execlist_ring_context {int dummy; } ;
struct drm_i915_gem_object {int dummy; } ;
struct TYPE_6__ {scalar_t__ shadow_pdps; } ;
struct TYPE_10__ {TYPE_1__ ppgtt_mm; int /*<<< orphan*/  pincount; } ;
struct TYPE_9__ {TYPE_3__* hw_context; } ;
struct TYPE_8__ {TYPE_2__* state; } ;
struct TYPE_7__ {struct drm_i915_gem_object* obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  LRC_STATE_PN ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 struct page* i915_gem_object_get_page (struct drm_i915_gem_object*,int /*<<< orphan*/ ) ; 
 struct execlist_ring_context* kmap (struct page*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 int /*<<< orphan*/  set_context_pdp_root_pointer (struct execlist_ring_context*,void*) ; 

__attribute__((used)) static void update_shadow_pdps(struct intel_vgpu_workload *workload)
{
	struct drm_i915_gem_object *ctx_obj =
		workload->req->hw_context->state->obj;
	struct execlist_ring_context *shadow_ring_context;
	struct page *page;

	if (WARN_ON(!workload->shadow_mm))
		return;

	if (WARN_ON(!atomic_read(&workload->shadow_mm->pincount)))
		return;

	page = i915_gem_object_get_page(ctx_obj, LRC_STATE_PN);
	shadow_ring_context = kmap(page);
	set_context_pdp_root_pointer(shadow_ring_context,
			(void *)workload->shadow_mm->ppgtt_mm.shadow_pdps);
	kunmap(page);
}