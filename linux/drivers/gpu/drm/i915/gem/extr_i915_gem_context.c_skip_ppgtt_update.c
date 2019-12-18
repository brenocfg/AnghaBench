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
struct intel_context {int /*<<< orphan*/  pin_count; int /*<<< orphan*/  state; TYPE_1__* engine; } ;
struct TYPE_2__ {int /*<<< orphan*/  i915; } ;

/* Variables and functions */
 scalar_t__ HAS_LOGICAL_RING_CONTEXTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool skip_ppgtt_update(struct intel_context *ce, void *data)
{
	if (HAS_LOGICAL_RING_CONTEXTS(ce->engine->i915))
		return !ce->state;
	else
		return !atomic_read(&ce->pin_count);
}