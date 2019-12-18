#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct intel_engine_cs {int /*<<< orphan*/  wa_list; int /*<<< orphan*/  uncore; } ;

/* Variables and functions */
 int /*<<< orphan*/  wa_list_apply (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void intel_engine_apply_workarounds(struct intel_engine_cs *engine)
{
	wa_list_apply(engine->uncore, &engine->wa_list);
}