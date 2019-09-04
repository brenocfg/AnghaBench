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
struct nlm_pic_irq {int /*<<< orphan*/  picirq; } ;
struct irq_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ack_c0_eirr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_c0_eimr (int /*<<< orphan*/ ) ; 
 struct nlm_pic_irq* irq_data_get_irq_chip_data (struct irq_data*) ; 

__attribute__((used)) static void xlp_pic_mask_ack(struct irq_data *d)
{
	struct nlm_pic_irq *pd = irq_data_get_irq_chip_data(d);

	clear_c0_eimr(pd->picirq);
	ack_c0_eirr(pd->picirq);
}