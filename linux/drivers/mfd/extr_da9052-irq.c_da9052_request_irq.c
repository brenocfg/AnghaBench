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
struct da9052 {int dummy; } ;
typedef  int /*<<< orphan*/  irq_handler_t ;

/* Variables and functions */
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_LOW ; 
 int da9052_map_irq (struct da9052*,int) ; 
 int request_threaded_irq (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,void*) ; 

int da9052_request_irq(struct da9052 *da9052, int irq, char *name,
			   irq_handler_t handler, void *data)
{
	irq = da9052_map_irq(da9052, irq);
	if (irq < 0)
		return irq;

	return request_threaded_irq(irq, NULL, handler,
				     IRQF_TRIGGER_LOW | IRQF_ONESHOT,
				     name, data);
}