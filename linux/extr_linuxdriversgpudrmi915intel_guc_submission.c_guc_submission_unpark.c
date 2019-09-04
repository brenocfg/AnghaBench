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
 int /*<<< orphan*/  intel_engine_pin_breadcrumbs_irq (struct intel_engine_cs*) ; 

__attribute__((used)) static void guc_submission_unpark(struct intel_engine_cs *engine)
{
	intel_engine_pin_breadcrumbs_irq(engine);
}