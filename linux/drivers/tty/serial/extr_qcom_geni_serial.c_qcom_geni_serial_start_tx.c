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
typedef  int u32 ;
struct uart_port {scalar_t__ membase; } ;

/* Variables and functions */
 int DEF_TX_WM ; 
 int M_CMD_DONE_EN ; 
 int M_GENI_CMD_ACTIVE ; 
 int M_TX_FIFO_WATERMARK_EN ; 
 scalar_t__ SE_GENI_M_IRQ_EN ; 
 scalar_t__ SE_GENI_STATUS ; 
 scalar_t__ SE_GENI_TX_WATERMARK_REG ; 
 int /*<<< orphan*/  qcom_geni_serial_tx_empty (struct uart_port*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void qcom_geni_serial_start_tx(struct uart_port *uport)
{
	u32 irq_en;
	u32 status;

	status = readl(uport->membase + SE_GENI_STATUS);
	if (status & M_GENI_CMD_ACTIVE)
		return;

	if (!qcom_geni_serial_tx_empty(uport))
		return;

	irq_en = readl(uport->membase +	SE_GENI_M_IRQ_EN);
	irq_en |= M_TX_FIFO_WATERMARK_EN | M_CMD_DONE_EN;

	writel(DEF_TX_WM, uport->membase + SE_GENI_TX_WATERMARK_REG);
	writel(irq_en, uport->membase +	SE_GENI_M_IRQ_EN);
}