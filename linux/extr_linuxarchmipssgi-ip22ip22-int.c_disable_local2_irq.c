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
struct irq_data {int irq; } ;
struct TYPE_2__ {int cmeimask0; int imask0; } ;

/* Variables and functions */
 int SGINT_LOCAL0 ; 
 int SGINT_LOCAL2 ; 
 int SGI_MAP_0_IRQ ; 
 TYPE_1__* sgint ; 

__attribute__((used)) static void disable_local2_irq(struct irq_data *d)
{
	sgint->cmeimask0 &= ~(1 << (d->irq - SGINT_LOCAL2));
	if (!sgint->cmeimask0)
		sgint->imask0 &= ~(1 << (SGI_MAP_0_IRQ - SGINT_LOCAL0));
}