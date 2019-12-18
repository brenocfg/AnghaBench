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
struct TYPE_2__ {int shared_phys; } ;
struct il_priv {TYPE_1__ _3945; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALM_SCD_ARASTAT_REG ; 
 int /*<<< orphan*/  ALM_SCD_MODE_REG ; 
 int /*<<< orphan*/  ALM_SCD_SBYP_MODE_1_REG ; 
 int /*<<< orphan*/  ALM_SCD_SBYP_MODE_2_REG ; 
 int /*<<< orphan*/  ALM_SCD_TXF4MF_REG ; 
 int /*<<< orphan*/  ALM_SCD_TXF5MF_REG ; 
 int /*<<< orphan*/  ALM_SCD_TXFACT_REG ; 
 int /*<<< orphan*/  FH39_TSSR_CBB_BASE ; 
 int /*<<< orphan*/  FH39_TSSR_MSG_CONFIG ; 
 int FH39_TSSR_TX_MSG_CONFIG_REG_VAL_MAX_FRAG_SIZE_128B ; 
 int FH39_TSSR_TX_MSG_CONFIG_REG_VAL_ORDER_RD_CBB_ON ; 
 int FH39_TSSR_TX_MSG_CONFIG_REG_VAL_ORDER_RD_TXPD_ON ; 
 int FH39_TSSR_TX_MSG_CONFIG_REG_VAL_ORDER_RSP_WAIT_TH ; 
 int FH39_TSSR_TX_MSG_CONFIG_REG_VAL_RSP_WAIT_TH ; 
 int FH39_TSSR_TX_MSG_CONFIG_REG_VAL_SNOOP_RD_TFD_ON ; 
 int FH39_TSSR_TX_MSG_CONFIG_REG_VAL_SNOOP_RD_TXPD_ON ; 
 int /*<<< orphan*/  il_wr (struct il_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  il_wr_prph (struct il_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
il3945_tx_reset(struct il_priv *il)
{
	/* bypass mode */
	il_wr_prph(il, ALM_SCD_MODE_REG, 0x2);

	/* RA 0 is active */
	il_wr_prph(il, ALM_SCD_ARASTAT_REG, 0x01);

	/* all 6 fifo are active */
	il_wr_prph(il, ALM_SCD_TXFACT_REG, 0x3f);

	il_wr_prph(il, ALM_SCD_SBYP_MODE_1_REG, 0x010000);
	il_wr_prph(il, ALM_SCD_SBYP_MODE_2_REG, 0x030002);
	il_wr_prph(il, ALM_SCD_TXF4MF_REG, 0x000004);
	il_wr_prph(il, ALM_SCD_TXF5MF_REG, 0x000005);

	il_wr(il, FH39_TSSR_CBB_BASE, il->_3945.shared_phys);

	il_wr(il, FH39_TSSR_MSG_CONFIG,
	      FH39_TSSR_TX_MSG_CONFIG_REG_VAL_SNOOP_RD_TXPD_ON |
	      FH39_TSSR_TX_MSG_CONFIG_REG_VAL_ORDER_RD_TXPD_ON |
	      FH39_TSSR_TX_MSG_CONFIG_REG_VAL_MAX_FRAG_SIZE_128B |
	      FH39_TSSR_TX_MSG_CONFIG_REG_VAL_SNOOP_RD_TFD_ON |
	      FH39_TSSR_TX_MSG_CONFIG_REG_VAL_ORDER_RD_CBB_ON |
	      FH39_TSSR_TX_MSG_CONFIG_REG_VAL_ORDER_RSP_WAIT_TH |
	      FH39_TSSR_TX_MSG_CONFIG_REG_VAL_RSP_WAIT_TH);

	return 0;
}