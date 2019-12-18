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
struct hvc_struct {int irq_requested; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  hvc_handle_interrupt ; 
 int request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct hvc_struct*) ; 

int notifier_add_irq(struct hvc_struct *hp, int irq)
{
	int rc;

	if (!irq) {
		hp->irq_requested = 0;
		return 0;
	}
	rc = request_irq(irq, hvc_handle_interrupt, hp->flags,
			"hvc_console", hp);
	if (!rc)
		hp->irq_requested = 1;
	return rc;
}