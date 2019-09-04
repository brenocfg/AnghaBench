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
struct xgene_enet_pdata {scalar_t__ enet_id; int /*<<< orphan*/  rx_pause; int /*<<< orphan*/  tx_pause; } ;

/* Variables and functions */
 int /*<<< orphan*/  AXGMAC_CONFIG_1 ; 
 int BIT (int) ; 
 int CFG_RSIF_FPBUFF_TIMEOUT_EN ; 
 int DEF_QUANTA ; 
 int HSTLENCHK ; 
 int HSTPPEN ; 
 int NORM_PAUSE_OPCODE ; 
 int RESUME_TX ; 
 int /*<<< orphan*/  RSIF_CLE_BUFF_THRESH_SET (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RSIF_PLC_CLE_BUFF_THRESH_SET (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XGENET_CSR_MULTI_DPF0_ADDR ; 
 int /*<<< orphan*/  XGENET_CSR_MULTI_DPF1_ADDR ; 
 int /*<<< orphan*/  XGENET_RX_DV_GATE_REG_0_ADDR ; 
 scalar_t__ XGENE_ENET1 ; 
 int /*<<< orphan*/  XG_CFG_BYPASS_ADDR ; 
 int XG_DEF_PAUSE_OFF_THRES ; 
 int XG_DEF_PAUSE_THRES ; 
 int /*<<< orphan*/  XG_ENET_SPARE_CFG_REG_1_ADDR ; 
 int /*<<< orphan*/  XG_ENET_SPARE_CFG_REG_ADDR ; 
 int /*<<< orphan*/  XG_RSIF_CLE_BUFF_THRESH ; 
 int /*<<< orphan*/  XG_RSIF_CONFIG1_REG_ADDR ; 
 int /*<<< orphan*/  XG_RSIF_CONFIG_REG_ADDR ; 
 int /*<<< orphan*/  XG_RSIF_PLC_CLE_BUFF_THRESH ; 
 int /*<<< orphan*/  XG_RXBUF_PAUSE_THRESH ; 
 int /*<<< orphan*/  xgene_enet_rd_axg_csr (struct xgene_enet_pdata*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  xgene_enet_rd_csr (struct xgene_enet_pdata*,int /*<<< orphan*/ ,int*) ; 
 int xgene_enet_rd_mac (struct xgene_enet_pdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgene_enet_wr_axg_csr (struct xgene_enet_pdata*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xgene_enet_wr_csr (struct xgene_enet_pdata*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xgene_enet_wr_mac (struct xgene_enet_pdata*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xgene_xgmac_flowctl_rx (struct xgene_enet_pdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgene_xgmac_flowctl_tx (struct xgene_enet_pdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgene_xgmac_reset (struct xgene_enet_pdata*) ; 
 int /*<<< orphan*/  xgene_xgmac_set_mac_addr (struct xgene_enet_pdata*) ; 

__attribute__((used)) static void xgene_xgmac_init(struct xgene_enet_pdata *pdata)
{
	u32 data;

	xgene_xgmac_reset(pdata);

	data = xgene_enet_rd_mac(pdata, AXGMAC_CONFIG_1);
	data |= HSTPPEN;
	data &= ~HSTLENCHK;
	xgene_enet_wr_mac(pdata, AXGMAC_CONFIG_1, data);

	xgene_xgmac_set_mac_addr(pdata);

	xgene_enet_rd_csr(pdata, XG_RSIF_CONFIG_REG_ADDR, &data);
	data |= CFG_RSIF_FPBUFF_TIMEOUT_EN;
	/* Errata 10GE_1 - FIFO threshold default value incorrect */
	RSIF_CLE_BUFF_THRESH_SET(&data, XG_RSIF_CLE_BUFF_THRESH);
	xgene_enet_wr_csr(pdata, XG_RSIF_CONFIG_REG_ADDR, data);

	/* Errata 10GE_1 - FIFO threshold default value incorrect */
	xgene_enet_rd_csr(pdata, XG_RSIF_CONFIG1_REG_ADDR, &data);
	RSIF_PLC_CLE_BUFF_THRESH_SET(&data, XG_RSIF_PLC_CLE_BUFF_THRESH);
	xgene_enet_wr_csr(pdata, XG_RSIF_CONFIG1_REG_ADDR, data);

	xgene_enet_rd_csr(pdata, XG_ENET_SPARE_CFG_REG_ADDR, &data);
	data |= BIT(12);
	xgene_enet_wr_csr(pdata, XG_ENET_SPARE_CFG_REG_ADDR, data);
	xgene_enet_wr_csr(pdata, XG_ENET_SPARE_CFG_REG_1_ADDR, 0x82);
	xgene_enet_wr_csr(pdata, XGENET_RX_DV_GATE_REG_0_ADDR, 0);
	xgene_enet_wr_csr(pdata, XG_CFG_BYPASS_ADDR, RESUME_TX);

	/* Configure HW pause frame generation */
	xgene_enet_rd_axg_csr(pdata, XGENET_CSR_MULTI_DPF0_ADDR, &data);
	data = (DEF_QUANTA << 16) | (data & 0xFFFF);
	xgene_enet_wr_axg_csr(pdata, XGENET_CSR_MULTI_DPF0_ADDR, data);

	if (pdata->enet_id != XGENE_ENET1) {
		xgene_enet_rd_axg_csr(pdata, XGENET_CSR_MULTI_DPF1_ADDR, &data);
		data = (NORM_PAUSE_OPCODE << 16) | (data & 0xFFFF);
		xgene_enet_wr_axg_csr(pdata, XGENET_CSR_MULTI_DPF1_ADDR, data);
	}

	data = (XG_DEF_PAUSE_OFF_THRES << 16) | XG_DEF_PAUSE_THRES;
	xgene_enet_wr_csr(pdata, XG_RXBUF_PAUSE_THRESH, data);

	xgene_xgmac_flowctl_tx(pdata, pdata->tx_pause);
	xgene_xgmac_flowctl_rx(pdata, pdata->rx_pause);
}