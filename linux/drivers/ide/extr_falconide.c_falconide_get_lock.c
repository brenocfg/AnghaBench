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
typedef  int /*<<< orphan*/  irq_handler_t ;

/* Variables and functions */
 int falconide_intr_lock ; 
 scalar_t__ in_interrupt () ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  stdma_lock (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void falconide_get_lock(irq_handler_t handler, void *data)
{
	if (falconide_intr_lock == 0) {
		if (in_interrupt() > 0)
			panic("Falcon IDE hasn't ST-DMA lock in interrupt");
		stdma_lock(handler, data);
		falconide_intr_lock = 1;
	}
}