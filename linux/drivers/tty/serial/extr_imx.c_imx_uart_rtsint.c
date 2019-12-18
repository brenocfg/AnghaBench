#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {int /*<<< orphan*/  lock; TYPE_2__* state; } ;
struct imx_port {TYPE_3__ port; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {int /*<<< orphan*/  delta_msr_wait; } ;
struct TYPE_5__ {TYPE_1__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  USR1 ; 
 int /*<<< orphan*/  USR1_RTSD ; 
 int USR1_RTSS ; 
 int imx_uart_readl (struct imx_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_uart_writel (struct imx_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uart_handle_cts_change (TYPE_3__*,int) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t imx_uart_rtsint(int irq, void *dev_id)
{
	struct imx_port *sport = dev_id;
	u32 usr1;

	spin_lock(&sport->port.lock);

	imx_uart_writel(sport, USR1_RTSD, USR1);
	usr1 = imx_uart_readl(sport, USR1) & USR1_RTSS;
	uart_handle_cts_change(&sport->port, !!usr1);
	wake_up_interruptible(&sport->port.state->port.delta_msr_wait);

	spin_unlock(&sport->port.lock);
	return IRQ_HANDLED;
}