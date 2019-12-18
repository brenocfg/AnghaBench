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
struct TYPE_2__ {int dma_chnl_num; } ;
struct il_priv {TYPE_1__ hw_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  FH49_TCSR_CHNL_TX_CONFIG_REG (int) ; 
 int /*<<< orphan*/  FH49_TSSR_TX_STATUS_REG ; 
 int /*<<< orphan*/  FH49_TSSR_TX_STATUS_REG_MSK_CHNL_IDLE (int) ; 
 int /*<<< orphan*/  IL49_SCD_TXFACT ; 
 int /*<<< orphan*/  IL_ERR (char*,int,int /*<<< orphan*/ ) ; 
 int _il_poll_bit (struct il_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _il_rd (struct il_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _il_wr (struct il_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _il_wr_prph (struct il_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
il4965_txq_ctx_stop(struct il_priv *il)
{
	int ch, ret;

	_il_wr_prph(il, IL49_SCD_TXFACT, 0);

	/* Stop each Tx DMA channel, and wait for it to be idle */
	for (ch = 0; ch < il->hw_params.dma_chnl_num; ch++) {
		_il_wr(il, FH49_TCSR_CHNL_TX_CONFIG_REG(ch), 0x0);
		ret =
		    _il_poll_bit(il, FH49_TSSR_TX_STATUS_REG,
				 FH49_TSSR_TX_STATUS_REG_MSK_CHNL_IDLE(ch),
				 FH49_TSSR_TX_STATUS_REG_MSK_CHNL_IDLE(ch),
				 1000);
		if (ret < 0)
			IL_ERR("Timeout stopping DMA channel %d [0x%08x]",
			       ch, _il_rd(il, FH49_TSSR_TX_STATUS_REG));
	}
}