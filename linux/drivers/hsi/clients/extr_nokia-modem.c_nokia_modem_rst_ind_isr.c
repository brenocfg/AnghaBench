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
struct nokia_modem_device {int /*<<< orphan*/  nokia_modem_rst_ind_tasklet; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t nokia_modem_rst_ind_isr(int irq, void *data)
{
	struct nokia_modem_device *modem = (struct nokia_modem_device *)data;

	tasklet_schedule(&modem->nokia_modem_rst_ind_tasklet);

	return IRQ_HANDLED;
}