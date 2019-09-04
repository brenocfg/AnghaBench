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
struct intel_engine_cs {int /*<<< orphan*/  last_retired_context; TYPE_2__* i915; } ;
struct intel_context {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  struct_mutex; } ;
struct TYPE_4__ {TYPE_1__ drm; } ;

/* Variables and functions */
 struct intel_context* fetch_and_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_context_unpin (struct intel_context*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

void intel_engine_lost_context(struct intel_engine_cs *engine)
{
	struct intel_context *ce;

	lockdep_assert_held(&engine->i915->drm.struct_mutex);

	ce = fetch_and_zero(&engine->last_retired_context);
	if (ce)
		intel_context_unpin(ce);
}