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
struct TYPE_2__ {scalar_t__ phyirq; int /*<<< orphan*/ * irqdomain; } ;
struct lan78xx_net {TYPE_1__ domain_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  irq_dispose_mapping (scalar_t__) ; 
 int /*<<< orphan*/  irq_domain_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lan78xx_remove_irq_domain(struct lan78xx_net *dev)
{
	if (dev->domain_data.phyirq > 0) {
		irq_dispose_mapping(dev->domain_data.phyirq);

		if (dev->domain_data.irqdomain)
			irq_domain_remove(dev->domain_data.irqdomain);
	}
	dev->domain_data.phyirq = 0;
	dev->domain_data.irqdomain = NULL;
}