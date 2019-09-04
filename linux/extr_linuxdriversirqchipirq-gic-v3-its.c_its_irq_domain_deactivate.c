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
typedef  int /*<<< orphan*/  u32 ;
struct its_device {int dummy; } ;
struct irq_domain {int dummy; } ;
struct irq_data {int dummy; } ;

/* Variables and functions */
 struct its_device* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  its_get_event_id (struct irq_data*) ; 
 int /*<<< orphan*/  its_send_discard (struct its_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void its_irq_domain_deactivate(struct irq_domain *domain,
				      struct irq_data *d)
{
	struct its_device *its_dev = irq_data_get_irq_chip_data(d);
	u32 event = its_get_event_id(d);

	/* Stop the delivery of interrupts */
	its_send_discard(its_dev, event);
}