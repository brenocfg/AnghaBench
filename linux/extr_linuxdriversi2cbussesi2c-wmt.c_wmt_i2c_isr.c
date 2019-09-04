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
struct wmt_i2c_dev {int /*<<< orphan*/  complete; scalar_t__ base; int /*<<< orphan*/  cmd_status; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ REG_ISR ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  readw (scalar_t__) ; 
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static irqreturn_t wmt_i2c_isr(int irq, void *data)
{
	struct wmt_i2c_dev *i2c_dev = data;

	/* save the status and write-clear it */
	i2c_dev->cmd_status = readw(i2c_dev->base + REG_ISR);
	writew(i2c_dev->cmd_status, i2c_dev->base + REG_ISR);

	complete(&i2c_dev->complete);

	return IRQ_HANDLED;
}