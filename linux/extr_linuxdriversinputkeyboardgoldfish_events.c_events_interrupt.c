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
struct event_dev {int /*<<< orphan*/  input; scalar_t__ addr; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ REG_READ ; 
 unsigned int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  input_event (int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t events_interrupt(int irq, void *dev_id)
{
	struct event_dev *edev = dev_id;
	unsigned int type, code, value;

	type = __raw_readl(edev->addr + REG_READ);
	code = __raw_readl(edev->addr + REG_READ);
	value = __raw_readl(edev->addr + REG_READ);

	input_event(edev->input, type, code, value);
	input_sync(edev->input);
	return IRQ_HANDLED;
}