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
struct TYPE_2__ {int int_disabled; int /*<<< orphan*/  dwork; } ;
struct hdm_i2c {TYPE_1__ rx; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  disable_irq_nosync (int) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t most_irq_handler(int irq, void *_dev)
{
	struct hdm_i2c *dev = _dev;

	disable_irq_nosync(irq);
	dev->rx.int_disabled = true;
	schedule_delayed_work(&dev->rx.dwork, 0);

	return IRQ_HANDLED;
}