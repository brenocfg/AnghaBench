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
struct irq_domain {int dummy; } ;
typedef  int irq_hw_number_t ;

/* Variables and functions */
#define  NPS_IPI_IRQ 129 
#define  NPS_TIMER0_IRQ 128 
 int /*<<< orphan*/  handle_fasteoi_irq ; 
 int /*<<< orphan*/  handle_percpu_devid_irq ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_percpu_devid (unsigned int) ; 
 int /*<<< orphan*/  nps400_irq_chip_fasteoi ; 
 int /*<<< orphan*/  nps400_irq_chip_percpu ; 

__attribute__((used)) static int nps400_irq_map(struct irq_domain *d, unsigned int virq,
			  irq_hw_number_t hw)
{
	switch (hw) {
	case NPS_TIMER0_IRQ:
#ifdef CONFIG_SMP
	case NPS_IPI_IRQ:
#endif
		irq_set_percpu_devid(virq);
		irq_set_chip_and_handler(virq, &nps400_irq_chip_percpu,
					 handle_percpu_devid_irq);
		break;
	default:
		irq_set_chip_and_handler(virq, &nps400_irq_chip_fasteoi,
					 handle_fasteoi_irq);
		break;
	}

	return 0;
}