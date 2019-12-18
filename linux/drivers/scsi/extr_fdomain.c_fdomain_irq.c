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
struct fdomain {int /*<<< orphan*/  work; int /*<<< orphan*/  cur_cmd; scalar_t__ base; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int ASTAT_IRQ ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ REG_ASTAT ; 
 scalar_t__ REG_ICTL ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t fdomain_irq(int irq, void *dev_id)
{
	struct fdomain *fd = dev_id;

	/* Is it our IRQ? */
	if ((inb(fd->base + REG_ASTAT) & ASTAT_IRQ) == 0)
		return IRQ_NONE;

	outb(0, fd->base + REG_ICTL);

	/* We usually have one spurious interrupt after each command. */
	if (!fd->cur_cmd)	/* Spurious interrupt */
		return IRQ_NONE;

	schedule_work(&fd->work);

	return IRQ_HANDLED;
}