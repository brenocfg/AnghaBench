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
struct rpisense_js {int /*<<< orphan*/  keys_work_s; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {struct rpisense_js joystick; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 TYPE_1__* rpisense ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t keys_irq_handler(int irq, void *pdev)
{
	struct rpisense_js *rpisense_js = &rpisense->joystick;

	schedule_work(&rpisense_js->keys_work_s);
	return IRQ_HANDLED;
}