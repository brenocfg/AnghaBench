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
struct TYPE_2__ {int /*<<< orphan*/  link; } ;
struct i915_request {int /*<<< orphan*/  engine; TYPE_1__ mock; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  i915_request_completed (struct i915_request*) ; 
 int /*<<< orphan*/  i915_request_mark_complete (struct i915_request*) ; 
 int /*<<< orphan*/  intel_engine_queue_breadcrumbs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void advance(struct i915_request *request)
{
	list_del_init(&request->mock.link);
	i915_request_mark_complete(request);
	GEM_BUG_ON(!i915_request_completed(request));

	intel_engine_queue_breadcrumbs(request->engine);
}