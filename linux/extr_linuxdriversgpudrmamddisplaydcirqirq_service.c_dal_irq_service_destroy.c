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
struct irq_service {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 int /*<<< orphan*/  kfree (struct irq_service*) ; 

void dal_irq_service_destroy(struct irq_service **irq_service)
{
	if (!irq_service || !*irq_service) {
		BREAK_TO_DEBUGGER();
		return;
	}

	kfree(*irq_service);

	*irq_service = NULL;
}