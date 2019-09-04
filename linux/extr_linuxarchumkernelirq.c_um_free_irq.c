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

/* Variables and functions */
 int /*<<< orphan*/  free_irq (unsigned int,void*) ; 
 int /*<<< orphan*/  free_irq_by_irq_and_dev (unsigned int,void*) ; 

void um_free_irq(unsigned int irq, void *dev)
{
	free_irq_by_irq_and_dev(irq, dev);
	free_irq(irq, dev);
}