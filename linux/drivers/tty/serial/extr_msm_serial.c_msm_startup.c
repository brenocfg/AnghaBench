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
struct uart_port {int line; int fifosize; int /*<<< orphan*/  irq; } ;
struct TYPE_2__ {int /*<<< orphan*/  mapbase; } ;
struct msm_port {int /*<<< orphan*/  clk; int /*<<< orphan*/  pclk; scalar_t__ is_uartdm; int /*<<< orphan*/  name; TYPE_1__ uart; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_TRIGGER_HIGH ; 
 unsigned int UART_DM_MR1_AUTO_RFR_LEVEL1 ; 
 int /*<<< orphan*/  UART_MR1 ; 
 unsigned int UART_MR1_AUTO_RFR_LEVEL0 ; 
 unsigned int UART_MR1_AUTO_RFR_LEVEL1 ; 
 struct msm_port* UART_TO_MSM (struct uart_port*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  msm_init_clock (struct uart_port*) ; 
 unsigned int msm_read (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_release_dma (struct msm_port*) ; 
 int /*<<< orphan*/  msm_request_rx_dma (struct msm_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_request_tx_dma (struct msm_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_uart_irq ; 
 int /*<<< orphan*/  msm_write (struct uart_port*,unsigned int,int /*<<< orphan*/ ) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uart_port*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int msm_startup(struct uart_port *port)
{
	struct msm_port *msm_port = UART_TO_MSM(port);
	unsigned int data, rfr_level, mask;
	int ret;

	snprintf(msm_port->name, sizeof(msm_port->name),
		 "msm_serial%d", port->line);

	msm_init_clock(port);

	if (likely(port->fifosize > 12))
		rfr_level = port->fifosize - 12;
	else
		rfr_level = port->fifosize;

	/* set automatic RFR level */
	data = msm_read(port, UART_MR1);

	if (msm_port->is_uartdm)
		mask = UART_DM_MR1_AUTO_RFR_LEVEL1;
	else
		mask = UART_MR1_AUTO_RFR_LEVEL1;

	data &= ~mask;
	data &= ~UART_MR1_AUTO_RFR_LEVEL0;
	data |= mask & (rfr_level << 2);
	data |= UART_MR1_AUTO_RFR_LEVEL0 & rfr_level;
	msm_write(port, data, UART_MR1);

	if (msm_port->is_uartdm) {
		msm_request_tx_dma(msm_port, msm_port->uart.mapbase);
		msm_request_rx_dma(msm_port, msm_port->uart.mapbase);
	}

	ret = request_irq(port->irq, msm_uart_irq, IRQF_TRIGGER_HIGH,
			  msm_port->name, port);
	if (unlikely(ret))
		goto err_irq;

	return 0;

err_irq:
	if (msm_port->is_uartdm)
		msm_release_dma(msm_port);

	clk_disable_unprepare(msm_port->pclk);
	clk_disable_unprepare(msm_port->clk);

	return ret;
}