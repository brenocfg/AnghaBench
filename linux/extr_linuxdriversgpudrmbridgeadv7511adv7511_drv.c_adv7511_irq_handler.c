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
struct adv7511 {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int adv7511_irq_process (struct adv7511*,int) ; 

__attribute__((used)) static irqreturn_t adv7511_irq_handler(int irq, void *devid)
{
	struct adv7511 *adv7511 = devid;
	int ret;

	ret = adv7511_irq_process(adv7511, true);
	return ret < 0 ? IRQ_NONE : IRQ_HANDLED;
}