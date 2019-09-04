#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  lock; } ;
struct TYPE_6__ {int mock; } ;
struct TYPE_5__ {void* page_addr; } ;
struct intel_engine_cs {int id; TYPE_3__ timeline; int /*<<< orphan*/  buffer; TYPE_2__ breadcrumbs; int /*<<< orphan*/  name; int /*<<< orphan*/  submit_request; int /*<<< orphan*/  emit_breadcrumb; int /*<<< orphan*/  emit_flush; int /*<<< orphan*/  request_alloc; int /*<<< orphan*/  context_pin; TYPE_1__ status_page; struct drm_i915_private* i915; } ;
struct mock_engine {struct intel_engine_cs base; int /*<<< orphan*/  hw_queue; int /*<<< orphan*/  hw_delay; int /*<<< orphan*/  hw_lock; } ;
struct drm_i915_private {int /*<<< orphan*/  kernel_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int I915_NUM_ENGINES ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  TIMELINE_ENGINE ; 
 int /*<<< orphan*/  hw_delay_complete ; 
 int /*<<< orphan*/  i915_timeline_fini (TYPE_3__*) ; 
 int /*<<< orphan*/  i915_timeline_init (struct drm_i915_private*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_context_pin (int /*<<< orphan*/ ,struct intel_engine_cs*) ; 
 int /*<<< orphan*/  intel_engine_fini_breadcrumbs (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  intel_engine_init_breadcrumbs (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  kfree (struct mock_engine*) ; 
 struct mock_engine* kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_set_subclass (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mock_context_pin ; 
 int /*<<< orphan*/  mock_emit_breadcrumb ; 
 int /*<<< orphan*/  mock_emit_flush ; 
 int /*<<< orphan*/  mock_request_alloc ; 
 int /*<<< orphan*/  mock_ring (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  mock_ring_free (int /*<<< orphan*/ ) ; 
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
	snprintf(engine->base.name, sizeof(engine->base.name), "%s", name);
	engine->base.id = id;
	engine->base.status_page.page_addr = (void *)(engine + 1);

	engine->base.context_pin = mock_context_pin;
	engine->base.request_alloc = mock_request_alloc;
	engine->base.emit_flush = mock_emit_flush;
	engine->base.emit_breadcrumb = mock_emit_breadcrumb;
	engine->base.submit_request = mock_submit_request;

	i915_timeline_init(i915, &engine->base.timeline, engine->base.name);
	lockdep_set_subclass(&engine->base.timeline.lock, TIMELINE_ENGINE);

	intel_engine_init_breadcrumbs(&engine->base);
	engine->base.breadcrumbs.mock = true; /* prevent touching HW for irqs */

	/* fake hw queue */
	spin_lock_init(&engine->hw_lock);
	timer_setup(&engine->hw_delay, hw_delay_complete, 0);
	INIT_LIST_HEAD(&engine->hw_queue);

	engine->base.buffer = mock_ring(&engine->base);
	if (!engine->base.buffer)
		goto err_breadcrumbs;

	if (IS_ERR(intel_context_pin(i915->kernel_context, &engine->base)))
		goto err_ring;

	return &engine->base;

err_ring:
	mock_ring_free(engine->base.buffer);
err_breadcrumbs:
	intel_engine_fini_breadcrumbs(&engine->base);
	i915_timeline_fini(&engine->base.timeline);
	kfree(engine);
	return NULL;
}