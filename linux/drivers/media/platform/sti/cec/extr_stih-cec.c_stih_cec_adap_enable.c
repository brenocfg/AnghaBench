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
struct stih_cec {scalar_t__ regs; int /*<<< orphan*/  clk; } ;
struct cec_adapter {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 scalar_t__ CEC_ADDR_TABLE ; 
 int CEC_BIT_HPULSE_03MS ; 
 int CEC_BIT_LPULSE_03MS ; 
 scalar_t__ CEC_BIT_PULSE_THRESH ; 
 scalar_t__ CEC_BIT_TOUT_THRESH ; 
 scalar_t__ CEC_CLK_DIV ; 
 scalar_t__ CEC_CTRL ; 
 scalar_t__ CEC_DATA_ARRAY_CTRL ; 
 int CEC_DBIT_TOUT_28MS ; 
 int CEC_EN ; 
 int CEC_ERROR_IRQ_EN ; 
 int CEC_IN_FILTER_EN ; 
 scalar_t__ CEC_IRQ_CTRL ; 
 int CEC_RX_ARRAY_EN ; 
 int CEC_RX_DONE_IRQ_EN ; 
 int CEC_RX_EOM_IRQ_EN ; 
 int CEC_RX_RESET_EN ; 
 int CEC_RX_SOM_IRQ_EN ; 
 int CEC_SBIT_TOUT_47MS ; 
 scalar_t__ CEC_STATUS ; 
 int CEC_TX_ARRAY_EN ; 
 scalar_t__ CEC_TX_CTRL ; 
 int CEC_TX_DONE_IRQ_EN ; 
 int CEC_TX_STOP_ON_NACK ; 
 struct stih_cec* cec_get_drvdata (struct cec_adapter*) ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int stih_cec_adap_enable(struct cec_adapter *adap, bool enable)
{
	struct stih_cec *cec = cec_get_drvdata(adap);

	if (enable) {
		/* The doc says (input TCLK_PERIOD * CEC_CLK_DIV) = 0.1ms */
		unsigned long clk_freq = clk_get_rate(cec->clk);
		u32 cec_clk_div = clk_freq / 10000;

		writel(cec_clk_div, cec->regs + CEC_CLK_DIV);

		/* Configuration of the durations activating a timeout */
		writel(CEC_SBIT_TOUT_47MS | (CEC_DBIT_TOUT_28MS << 4),
		       cec->regs + CEC_BIT_TOUT_THRESH);

		/* Configuration of the smallest allowed duration for pulses */
		writel(CEC_BIT_LPULSE_03MS | CEC_BIT_HPULSE_03MS,
		       cec->regs + CEC_BIT_PULSE_THRESH);

		/* Minimum received bit period threshold */
		writel(BIT(5) | BIT(7), cec->regs + CEC_TX_CTRL);

		/* Configuration of transceiver data arrays */
		writel(CEC_TX_ARRAY_EN | CEC_RX_ARRAY_EN | CEC_TX_STOP_ON_NACK,
		       cec->regs + CEC_DATA_ARRAY_CTRL);

		/* Configuration of the control bits for CEC Transceiver */
		writel(CEC_IN_FILTER_EN | CEC_EN | CEC_RX_RESET_EN,
		       cec->regs + CEC_CTRL);

		/* Clear logical addresses */
		writel(0, cec->regs + CEC_ADDR_TABLE);

		/* Clear the status register */
		writel(0x0, cec->regs + CEC_STATUS);

		/* Enable the interrupts */
		writel(CEC_TX_DONE_IRQ_EN | CEC_RX_DONE_IRQ_EN |
		       CEC_RX_SOM_IRQ_EN | CEC_RX_EOM_IRQ_EN |
		       CEC_ERROR_IRQ_EN,
		       cec->regs + CEC_IRQ_CTRL);

	} else {
		/* Clear logical addresses */
		writel(0, cec->regs + CEC_ADDR_TABLE);

		/* Clear the status register */
		writel(0x0, cec->regs + CEC_STATUS);

		/* Disable the interrupts */
		writel(0, cec->regs + CEC_IRQ_CTRL);
	}

	return 0;
}