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
struct of_phandle_args {int dummy; } ;
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  irq_handler_t ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 unsigned int irq_create_of_mapping (struct of_phandle_args*) ; 
 scalar_t__ of_irq_parse_one (struct device_node*,int,struct of_phandle_args*) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int,...) ; 
 scalar_t__ request_irq (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

void request_event_sources_irqs(struct device_node *np,
				irq_handler_t handler,
				const char *name)
{
	int i, index, count = 0;
	struct of_phandle_args oirq;
	unsigned int virqs[16];

	/* First try to do a proper OF tree parsing */
	for (index = 0; of_irq_parse_one(np, index, &oirq) == 0;
	     index++) {
		if (count > 15)
			break;
		virqs[count] = irq_create_of_mapping(&oirq);
		if (!virqs[count]) {
			pr_err("event-sources: Unable to allocate "
			       "interrupt number for %pOF\n",
			       np);
			WARN_ON(1);
		} else {
			count++;
		}
	}

	/* Now request them */
	for (i = 0; i < count; i++) {
		if (request_irq(virqs[i], handler, 0, name, NULL)) {
			pr_err("event-sources: Unable to request interrupt "
			       "%d for %pOF\n", virqs[i], np);
			WARN_ON(1);
			return;
		}
	}
}