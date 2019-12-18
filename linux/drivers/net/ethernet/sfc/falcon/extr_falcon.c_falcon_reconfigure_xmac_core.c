#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int fc; } ;
struct ef4_nic {TYPE_2__* net_dev; int /*<<< orphan*/  unicast_filter; TYPE_1__ link_state; } ;
typedef  int /*<<< orphan*/  ef4_oword_t ;
struct TYPE_4__ {int /*<<< orphan*/ * dev_addr; int /*<<< orphan*/  mtu; } ;

/* Variables and functions */
 int EF4_FC_RX ; 
 int EF4_FC_TX ; 
 unsigned int EF4_MAX_FRAME_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EF4_POPULATE_OWORD_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  EF4_POPULATE_OWORD_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EF4_POPULATE_OWORD_3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EF4_POPULATE_OWORD_5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EF4_POPULATE_OWORD_6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FRF_AB_XM_ACPT_ALL_MCAST ; 
 int /*<<< orphan*/  FRF_AB_XM_ACPT_ALL_UCAST ; 
 int /*<<< orphan*/  FRF_AB_XM_AUTO_DEPAD ; 
 int /*<<< orphan*/  FRF_AB_XM_AUTO_PAD ; 
 int /*<<< orphan*/  FRF_AB_XM_DIS_FCNTL ; 
 int /*<<< orphan*/  FRF_AB_XM_FCNTL ; 
 int /*<<< orphan*/  FRF_AB_XM_IPG ; 
 int /*<<< orphan*/  FRF_AB_XM_MAX_RX_FRM_SIZE ; 
 int /*<<< orphan*/  FRF_AB_XM_MAX_TX_FRM_SIZE ; 
 int /*<<< orphan*/  FRF_AB_XM_PASS_CRC_ERR ; 
 int /*<<< orphan*/  FRF_AB_XM_PAUSE_TIME ; 
 int /*<<< orphan*/  FRF_AB_XM_RXEN ; 
 int /*<<< orphan*/  FRF_AB_XM_RX_JUMBO_MODE ; 
 int /*<<< orphan*/  FRF_AB_XM_RX_STAT_EN ; 
 int /*<<< orphan*/  FRF_AB_XM_TXCRC ; 
 int /*<<< orphan*/  FRF_AB_XM_TXEN ; 
 int /*<<< orphan*/  FRF_AB_XM_TX_JUMBO_MODE ; 
 int /*<<< orphan*/  FRF_AB_XM_TX_PRMBL ; 
 int /*<<< orphan*/  FRF_AB_XM_TX_STAT_EN ; 
 int /*<<< orphan*/  FR_AB_XM_ADR_HI ; 
 int /*<<< orphan*/  FR_AB_XM_ADR_LO ; 
 int /*<<< orphan*/  FR_AB_XM_FC ; 
 int /*<<< orphan*/  FR_AB_XM_GLB_CFG ; 
 int /*<<< orphan*/  FR_AB_XM_RX_CFG ; 
 int /*<<< orphan*/  FR_AB_XM_RX_PARAM ; 
 int /*<<< orphan*/  FR_AB_XM_TX_CFG ; 
 int /*<<< orphan*/  FR_AB_XM_TX_PARAM ; 
 int /*<<< orphan*/  ef4_writeo (struct ef4_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void falcon_reconfigure_xmac_core(struct ef4_nic *efx)
{
	unsigned int max_frame_len;
	ef4_oword_t reg;
	bool rx_fc = !!(efx->link_state.fc & EF4_FC_RX);
	bool tx_fc = !!(efx->link_state.fc & EF4_FC_TX);

	/* Configure MAC  - cut-thru mode is hard wired on */
	EF4_POPULATE_OWORD_3(reg,
			     FRF_AB_XM_RX_JUMBO_MODE, 1,
			     FRF_AB_XM_TX_STAT_EN, 1,
			     FRF_AB_XM_RX_STAT_EN, 1);
	ef4_writeo(efx, &reg, FR_AB_XM_GLB_CFG);

	/* Configure TX */
	EF4_POPULATE_OWORD_6(reg,
			     FRF_AB_XM_TXEN, 1,
			     FRF_AB_XM_TX_PRMBL, 1,
			     FRF_AB_XM_AUTO_PAD, 1,
			     FRF_AB_XM_TXCRC, 1,
			     FRF_AB_XM_FCNTL, tx_fc,
			     FRF_AB_XM_IPG, 0x3);
	ef4_writeo(efx, &reg, FR_AB_XM_TX_CFG);

	/* Configure RX */
	EF4_POPULATE_OWORD_5(reg,
			     FRF_AB_XM_RXEN, 1,
			     FRF_AB_XM_AUTO_DEPAD, 0,
			     FRF_AB_XM_ACPT_ALL_MCAST, 1,
			     FRF_AB_XM_ACPT_ALL_UCAST, !efx->unicast_filter,
			     FRF_AB_XM_PASS_CRC_ERR, 1);
	ef4_writeo(efx, &reg, FR_AB_XM_RX_CFG);

	/* Set frame length */
	max_frame_len = EF4_MAX_FRAME_LEN(efx->net_dev->mtu);
	EF4_POPULATE_OWORD_1(reg, FRF_AB_XM_MAX_RX_FRM_SIZE, max_frame_len);
	ef4_writeo(efx, &reg, FR_AB_XM_RX_PARAM);
	EF4_POPULATE_OWORD_2(reg,
			     FRF_AB_XM_MAX_TX_FRM_SIZE, max_frame_len,
			     FRF_AB_XM_TX_JUMBO_MODE, 1);
	ef4_writeo(efx, &reg, FR_AB_XM_TX_PARAM);

	EF4_POPULATE_OWORD_2(reg,
			     FRF_AB_XM_PAUSE_TIME, 0xfffe, /* MAX PAUSE TIME */
			     FRF_AB_XM_DIS_FCNTL, !rx_fc);
	ef4_writeo(efx, &reg, FR_AB_XM_FC);

	/* Set MAC address */
	memcpy(&reg, &efx->net_dev->dev_addr[0], 4);
	ef4_writeo(efx, &reg, FR_AB_XM_ADR_LO);
	memcpy(&reg, &efx->net_dev->dev_addr[4], 2);
	ef4_writeo(efx, &reg, FR_AB_XM_ADR_HI);
}