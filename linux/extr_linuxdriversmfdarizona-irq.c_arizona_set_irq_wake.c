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
struct arizona {int dummy; } ;

/* Variables and functions */
 int arizona_map_irq (struct arizona*,int) ; 
 int irq_set_irq_wake (int,int) ; 

int arizona_set_irq_wake(struct arizona *arizona, int irq, int on)
{
	irq = arizona_map_irq(arizona, irq);
	if (irq < 0)
		return irq;

	return irq_set_irq_wake(irq, on);
}