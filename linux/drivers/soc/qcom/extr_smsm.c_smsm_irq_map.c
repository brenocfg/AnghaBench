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
struct smsm_entry {int dummy; } ;
struct irq_domain {struct smsm_entry* host_data; } ;
typedef  int /*<<< orphan*/  irq_hw_number_t ;

/* Variables and functions */
 int /*<<< orphan*/  handle_level_irq ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chip_data (unsigned int,struct smsm_entry*) ; 
 int /*<<< orphan*/  irq_set_nested_thread (unsigned int,int) ; 
 int /*<<< orphan*/  smsm_irq_chip ; 

__attribute__((used)) static int smsm_irq_map(struct irq_domain *d,
			unsigned int irq,
			irq_hw_number_t hw)
{
	struct smsm_entry *entry = d->host_data;

	irq_set_chip_and_handler(irq, &smsm_irq_chip, handle_level_irq);
	irq_set_chip_data(irq, entry);
	irq_set_nested_thread(irq, 1);

	return 0;
}