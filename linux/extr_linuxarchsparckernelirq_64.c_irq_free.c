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
 int /*<<< orphan*/  irq_free_descs (unsigned int,int) ; 
 void* irq_get_handler_data (unsigned int) ; 
 int /*<<< orphan*/  irq_set_handler_data (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (void*) ; 

void irq_free(unsigned int irq)
{
	void *data = irq_get_handler_data(irq);

	kfree(data);
	irq_set_handler_data(irq, NULL);
	irq_free_descs(irq, 1);
}