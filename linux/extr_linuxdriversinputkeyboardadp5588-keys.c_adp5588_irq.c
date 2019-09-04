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
struct adp5588_kpad {int /*<<< orphan*/  delay; int /*<<< orphan*/  work; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t adp5588_irq(int irq, void *handle)
{
	struct adp5588_kpad *kpad = handle;

	/*
	 * use keventd context to read the event fifo registers
	 * Schedule readout at least 25ms after notification for
	 * REVID < 4
	 */

	schedule_delayed_work(&kpad->work, kpad->delay);

	return IRQ_HANDLED;
}