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
struct wcn36xx {int /*<<< orphan*/  dxe_tx_l_ch; int /*<<< orphan*/  dxe_tx_h_ch; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int WCN36XX_CH_STAT_INT_DONE_MASK ; 
 int WCN36XX_CH_STAT_INT_ED_MASK ; 
 int WCN36XX_CH_STAT_INT_ERR_MASK ; 
 int /*<<< orphan*/  WCN36XX_DBG_DXE ; 
 int /*<<< orphan*/  WCN36XX_DXE_0_INT_CLR ; 
 int /*<<< orphan*/  WCN36XX_DXE_0_INT_DONE_CLR ; 
 int /*<<< orphan*/  WCN36XX_DXE_0_INT_ED_CLR ; 
 int /*<<< orphan*/  WCN36XX_DXE_0_INT_ERR_CLR ; 
 int /*<<< orphan*/  WCN36XX_DXE_CH_STATUS_REG_ADDR_TX_H ; 
 int /*<<< orphan*/  WCN36XX_DXE_CH_STATUS_REG_ADDR_TX_L ; 
 int /*<<< orphan*/  WCN36XX_DXE_INT_SRC_RAW_REG ; 
 int WCN36XX_INT_MASK_CHAN_TX_H ; 
 int WCN36XX_INT_MASK_CHAN_TX_L ; 
 int /*<<< orphan*/  reap_tx_dxes (struct wcn36xx*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wcn36xx_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wcn36xx_dxe_read_register (struct wcn36xx*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  wcn36xx_dxe_write_register (struct wcn36xx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wcn36xx_err (char*,int) ; 

__attribute__((used)) static irqreturn_t wcn36xx_irq_tx_complete(int irq, void *dev)
{
	struct wcn36xx *wcn = (struct wcn36xx *)dev;
	int int_src, int_reason;

	wcn36xx_dxe_read_register(wcn, WCN36XX_DXE_INT_SRC_RAW_REG, &int_src);

	if (int_src & WCN36XX_INT_MASK_CHAN_TX_H) {
		wcn36xx_dxe_read_register(wcn,
					  WCN36XX_DXE_CH_STATUS_REG_ADDR_TX_H,
					  &int_reason);

		wcn36xx_dxe_write_register(wcn,
					   WCN36XX_DXE_0_INT_CLR,
					   WCN36XX_INT_MASK_CHAN_TX_H);

		if (int_reason & WCN36XX_CH_STAT_INT_ERR_MASK ) {
			wcn36xx_dxe_write_register(wcn,
						   WCN36XX_DXE_0_INT_ERR_CLR,
						   WCN36XX_INT_MASK_CHAN_TX_H);

			wcn36xx_err("DXE IRQ reported error: 0x%x in high TX channel\n",
					int_src);
		}

		if (int_reason & WCN36XX_CH_STAT_INT_DONE_MASK) {
			wcn36xx_dxe_write_register(wcn,
						   WCN36XX_DXE_0_INT_DONE_CLR,
						   WCN36XX_INT_MASK_CHAN_TX_H);
		}

		if (int_reason & WCN36XX_CH_STAT_INT_ED_MASK) {
			wcn36xx_dxe_write_register(wcn,
						   WCN36XX_DXE_0_INT_ED_CLR,
						   WCN36XX_INT_MASK_CHAN_TX_H);
		}

		wcn36xx_dbg(WCN36XX_DBG_DXE, "dxe tx ready high, reason %08x\n",
			    int_reason);

		if (int_reason & (WCN36XX_CH_STAT_INT_DONE_MASK |
				  WCN36XX_CH_STAT_INT_ED_MASK))
			reap_tx_dxes(wcn, &wcn->dxe_tx_h_ch);
	}

	if (int_src & WCN36XX_INT_MASK_CHAN_TX_L) {
		wcn36xx_dxe_read_register(wcn,
					  WCN36XX_DXE_CH_STATUS_REG_ADDR_TX_L,
					  &int_reason);

		wcn36xx_dxe_write_register(wcn,
					   WCN36XX_DXE_0_INT_CLR,
					   WCN36XX_INT_MASK_CHAN_TX_L);


		if (int_reason & WCN36XX_CH_STAT_INT_ERR_MASK ) {
			wcn36xx_dxe_write_register(wcn,
						   WCN36XX_DXE_0_INT_ERR_CLR,
						   WCN36XX_INT_MASK_CHAN_TX_L);

			wcn36xx_err("DXE IRQ reported error: 0x%x in low TX channel\n",
					int_src);
		}

		if (int_reason & WCN36XX_CH_STAT_INT_DONE_MASK) {
			wcn36xx_dxe_write_register(wcn,
						   WCN36XX_DXE_0_INT_DONE_CLR,
						   WCN36XX_INT_MASK_CHAN_TX_L);
		}

		if (int_reason & WCN36XX_CH_STAT_INT_ED_MASK) {
			wcn36xx_dxe_write_register(wcn,
						   WCN36XX_DXE_0_INT_ED_CLR,
						   WCN36XX_INT_MASK_CHAN_TX_L);
		}

		wcn36xx_dbg(WCN36XX_DBG_DXE, "dxe tx ready low, reason %08x\n",
			    int_reason);

		if (int_reason & (WCN36XX_CH_STAT_INT_DONE_MASK |
				  WCN36XX_CH_STAT_INT_ED_MASK))
			reap_tx_dxes(wcn, &wcn->dxe_tx_l_ch);
	}

	return IRQ_HANDLED;
}