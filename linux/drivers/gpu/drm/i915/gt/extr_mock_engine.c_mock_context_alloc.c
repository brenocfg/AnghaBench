#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct intel_context {int /*<<< orphan*/  timeline; TYPE_1__* engine; int /*<<< orphan*/  ring; } ;
struct TYPE_3__ {int /*<<< orphan*/  gt; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GEM_BUG_ON (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_timeline_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  mock_ring (TYPE_1__*) ; 
 int /*<<< orphan*/  mock_timeline_pin (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mock_context_alloc(struct intel_context *ce)
{
	ce->ring = mock_ring(ce->engine);
	if (!ce->ring)
		return -ENOMEM;

	GEM_BUG_ON(ce->timeline);
	ce->timeline = intel_timeline_create(ce->engine->gt, NULL);
	if (IS_ERR(ce->timeline)) {
		kfree(ce->engine);
		return PTR_ERR(ce->timeline);
	}

	mock_timeline_pin(ce->timeline);

	return 0;
}