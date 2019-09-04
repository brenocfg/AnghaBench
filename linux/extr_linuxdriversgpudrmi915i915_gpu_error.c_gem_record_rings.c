#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct intel_ring {int /*<<< orphan*/  vma; int /*<<< orphan*/  tail; int /*<<< orphan*/  head; } ;
struct TYPE_8__ {int /*<<< orphan*/  vma; } ;
struct TYPE_7__ {int /*<<< orphan*/  vma; } ;
struct intel_engine_cs {int /*<<< orphan*/  default_state; TYPE_4__ wa_ctx; TYPE_3__ status_page; int /*<<< orphan*/  scratch; } ;
struct i915_request {struct intel_ring* ring; int /*<<< orphan*/  tail; int /*<<< orphan*/  postfix; int /*<<< orphan*/  head; TYPE_2__* hw_context; int /*<<< orphan*/  batch; struct i915_gem_context* gem_context; } ;
struct i915_gpu_state {int /*<<< orphan*/  simulated; struct drm_i915_error_engine* engine; struct drm_i915_private* i915; } ;
struct i915_ggtt {int /*<<< orphan*/  vm; } ;
struct i915_gem_context {TYPE_1__* ppgtt; } ;
struct drm_i915_private {struct intel_engine_cs** engine; struct i915_ggtt ggtt; } ;
struct drm_i915_error_engine {int engine_id; int /*<<< orphan*/  default_state; void* wa_ctx; void* hws_page; void* ringbuffer; int /*<<< orphan*/  cpu_ring_tail; int /*<<< orphan*/  cpu_ring_head; int /*<<< orphan*/  rq_tail; int /*<<< orphan*/  rq_post; int /*<<< orphan*/  rq_head; void* ctx; void* wa_batchbuffer; void* batchbuffer; int /*<<< orphan*/  context; int /*<<< orphan*/ * vm; } ;
struct TYPE_6__ {int /*<<< orphan*/  state; } ;
struct TYPE_5__ {int /*<<< orphan*/  vm; } ;

/* Variables and functions */
 scalar_t__ HAS_BROKEN_CS_TLB (struct drm_i915_private*) ; 
 int I915_NUM_ENGINES ; 
 int /*<<< orphan*/  capture_object (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  engine_record_requests (struct intel_engine_cs*,struct i915_request*,struct drm_i915_error_engine*) ; 
 int /*<<< orphan*/  error_record_engine_execlists (struct intel_engine_cs*,struct drm_i915_error_engine*) ; 
 int /*<<< orphan*/  error_record_engine_registers (struct i915_gpu_state*,struct intel_engine_cs*,struct drm_i915_error_engine*) ; 
 int /*<<< orphan*/  error_record_engine_waiters (struct intel_engine_cs*,struct drm_i915_error_engine*) ; 
 void* i915_error_object_create (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_context_no_error_capture (struct i915_gem_context*) ; 
 struct i915_request* i915_gem_find_active_request (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  record_context (int /*<<< orphan*/ *,struct i915_gem_context*) ; 
 int /*<<< orphan*/  request_record_user_bo (struct i915_request*,struct drm_i915_error_engine*) ; 

__attribute__((used)) static void gem_record_rings(struct i915_gpu_state *error)
{
	struct drm_i915_private *i915 = error->i915;
	struct i915_ggtt *ggtt = &i915->ggtt;
	int i;

	for (i = 0; i < I915_NUM_ENGINES; i++) {
		struct intel_engine_cs *engine = i915->engine[i];
		struct drm_i915_error_engine *ee = &error->engine[i];
		struct i915_request *request;

		ee->engine_id = -1;

		if (!engine)
			continue;

		ee->engine_id = i;

		error_record_engine_registers(error, engine, ee);
		error_record_engine_waiters(engine, ee);
		error_record_engine_execlists(engine, ee);

		request = i915_gem_find_active_request(engine);
		if (request) {
			struct i915_gem_context *ctx = request->gem_context;
			struct intel_ring *ring;

			ee->vm = ctx->ppgtt ? &ctx->ppgtt->vm : &ggtt->vm;

			record_context(&ee->context, ctx);

			/* We need to copy these to an anonymous buffer
			 * as the simplest method to avoid being overwritten
			 * by userspace.
			 */
			ee->batchbuffer =
				i915_error_object_create(i915, request->batch);

			if (HAS_BROKEN_CS_TLB(i915))
				ee->wa_batchbuffer =
					i915_error_object_create(i915,
								 engine->scratch);
			request_record_user_bo(request, ee);

			ee->ctx =
				i915_error_object_create(i915,
							 request->hw_context->state);

			error->simulated |=
				i915_gem_context_no_error_capture(ctx);

			ee->rq_head = request->head;
			ee->rq_post = request->postfix;
			ee->rq_tail = request->tail;

			ring = request->ring;
			ee->cpu_ring_head = ring->head;
			ee->cpu_ring_tail = ring->tail;
			ee->ringbuffer =
				i915_error_object_create(i915, ring->vma);

			engine_record_requests(engine, request, ee);
		}

		ee->hws_page =
			i915_error_object_create(i915,
						 engine->status_page.vma);

		ee->wa_ctx = i915_error_object_create(i915, engine->wa_ctx.vma);

		ee->default_state = capture_object(i915, engine->default_state);
	}
}