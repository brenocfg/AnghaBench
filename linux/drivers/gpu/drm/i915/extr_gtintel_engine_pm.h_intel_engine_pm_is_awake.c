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
struct intel_engine_cs {int /*<<< orphan*/  wakeref; } ;

/* Variables and functions */
 int intel_wakeref_is_active (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool
intel_engine_pm_is_awake(const struct intel_engine_cs *engine)
{
	return intel_wakeref_is_active(&engine->wakeref);
}