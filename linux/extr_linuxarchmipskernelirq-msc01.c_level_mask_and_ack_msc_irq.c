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
struct irq_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSC01_IC_EOI ; 
 int /*<<< orphan*/  MSCIC_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_has_veic ; 
 int /*<<< orphan*/  mask_msc_irq (struct irq_data*) ; 

__attribute__((used)) static void level_mask_and_ack_msc_irq(struct irq_data *d)
{
	mask_msc_irq(d);
	if (!cpu_has_veic)
		MSCIC_WRITE(MSC01_IC_EOI, 0);
}