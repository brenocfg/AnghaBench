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
struct intel_engine_cs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IGT_IDLE_TIMEOUT ; 
 int /*<<< orphan*/  intel_engine_is_idle (struct intel_engine_cs*) ; 
 scalar_t__ wait_for (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool wait_for_idle(struct intel_engine_cs *engine)
{
	return wait_for(intel_engine_is_idle(engine), IGT_IDLE_TIMEOUT) == 0;
}