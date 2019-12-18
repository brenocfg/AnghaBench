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
struct TYPE_4__ {int /*<<< orphan*/  finish; int /*<<< orphan*/  reset; int /*<<< orphan*/  prepare; } ;
struct TYPE_3__ {void* addr; } ;
struct intel_engine_cs {int id; int instance; int /*<<< orphan*/  cancel_requests; TYPE_2__ reset; int /*<<< orphan*/  submit_request; int /*<<< orphan*/  emit_fini_breadcrumb; int /*<<< orphan*/  emit_flush; int /*<<< orphan*/  request_alloc; int /*<<< orphan*/ * cops; TYPE_1__ status_page; int /*<<< orphan*/  mask; int /*<<< orphan*/  name; int /*<<< orphan*/ * gt; struct drm_i915_private* i915; } ;
struct mock_engine {struct intel_engine_cs base; int /*<<< orphan*/  hw_queue; int /*<<< orphan*/  hw_delay; int /*<<< orphan*/  hw_lock; } ;
struct drm_i915_private {int /*<<< orphan*/  gt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int I915_NUM_ENGINES ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  hw_delay_complete ; 
 int /*<<< orphan*/  intel_engine_add_user (struct intel_engine_cs*) ; 
 struct mock_engine* kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mock_cancel_requests ; 
 int /*<<< orphan*/  mock_context_ops ; 
 int /*<<< orphan*/  mock_emit_breadcrumb ; 
 int /*<<< orphan*/  mock_emit_flush ; 
 int /*<<< orphan*/  mock_request_alloc ; 
 int /*<<< orphan*/  mock_reset ; 
 int /*<<< orphan*/  mock_reset_finish ; 
 int /*<<< orphan*/  mock_reset_prepare ; 
 int /*<<< orphan*/  mock_submit_request ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char const*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct intel_engine_cs *mock_engine(struct drm_i915_private *i915,
				    const char *name,
				    int id)
{
	struct mock_engine *engine;

	GEM_BUG_ON(id >= I915_NUM_ENGINES);

	engine = kzalloc(sizeof(*engine) + PAGE_SIZE, GFP_KERNEL);
	if (!engine)
		return NULL;

	/* minimal engine setup for requests */
	engine->base.i915 = i915;
	engine->base.gt = &i915->gt;
	snprintf(engine->base.name, sizeof(engine->base.name), "%s", name);
	engine->base.id = id;
	engine->base.mask = BIT(id);
	engine->base.instance = id;
	engine->base.status_page.addr = (void *)(engine + 1);

	engine->base.cops = &mock_context_ops;
	engine->base.request_alloc = mock_request_alloc;
	engine->base.emit_flush = mock_emit_flush;
	engine->base.emit_fini_breadcrumb = mock_emit_breadcrumb;
	engine->base.submit_request = mock_submit_request;

	engine->base.reset.prepare = mock_reset_prepare;
	engine->base.reset.reset = mock_reset;
	engine->base.reset.finish = mock_reset_finish;
	engine->base.cancel_requests = mock_cancel_requests;

	/* fake hw queue */
	spin_lock_init(&engine->hw_lock);
	timer_setup(&engine->hw_delay, hw_delay_complete, 0);
	INIT_LIST_HEAD(&engine->hw_queue);

	intel_engine_add_user(&engine->base);

	return &engine->base;
}