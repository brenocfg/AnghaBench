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
struct xgene_enet_pdata {scalar_t__ enet_id; int port_id; int /*<<< orphan*/  rx_pause; int /*<<< orphan*/  tx_pause; scalar_t__ mdio_driver; } ;

/* Variables and functions */
 int CFG_BYPASS_ADDR ; 
 int CFG_RSIF_FPBUFF_TIMEOUT_EN ; 
 int CSR_MULTI_DPF0_ADDR ; 
 int DEF_PAUSE_OFF_THRES ; 
 int DEF_PAUSE_THRES ; 
 int DEF_QUANTA ; 
 int ENET_SPARE_CFG_REG_ADDR ; 
 int /*<<< orphan*/  MGMT_CLOCK_SEL_SET (int*,int) ; 
 int /*<<< orphan*/  MII_MGMT_CONFIG_ADDR ; 
 int MPA_IDLE_WITH_QMI_EMPTY ; 
 int NORM_PAUSE_OPCODE ; 
 int OFFSET_4 ; 
 int RESUME_RX0 ; 
 int RESUME_TX ; 
 int RSIF_CONFIG_REG_ADDR ; 
 int RXBUF_PAUSE_OFF_THRESH ; 
 int RXBUF_PAUSE_THRESH ; 
 int SG_RX_DV_GATE_REG_0_ADDR ; 
 scalar_t__ XGENE_ENET1 ; 
 scalar_t__ XGENE_ENET2 ; 
 int XG_CFG_BYPASS_ADDR ; 
 int XG_ENET_SPARE_CFG_REG_1_ADDR ; 
 int XG_ENET_SPARE_CFG_REG_ADDR ; 
 int XG_MCX_MULTI_DPF0_ADDR ; 
 int XG_MCX_MULTI_DPF1_ADDR ; 
 int XG_MCX_RX_DV_GATE_REG_0_ADDR ; 
 int XG_RSIF_CONFIG_REG_ADDR ; 
 int XG_RXBUF_PAUSE_THRESH ; 
 int xgene_enet_rd_csr (struct xgene_enet_pdata*,int) ; 
 int xgene_enet_rd_mac (struct xgene_enet_pdata*,int /*<<< orphan*/ ) ; 
 int xgene_enet_rd_mcx_csr (struct xgene_enet_pdata*,int) ; 
 int /*<<< orphan*/  xgene_enet_wr_csr (struct xgene_enet_pdata*,int,int) ; 
 int /*<<< orphan*/  xgene_enet_wr_mac (struct xgene_enet_pdata*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xgene_enet_wr_mcx_csr (struct xgene_enet_pdata*,int,int) ; 
 int /*<<< orphan*/  xgene_sgmac_flowctl_rx (struct xgene_enet_pdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgene_sgmac_flowctl_tx (struct xgene_enet_pdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgene_sgmac_reset (struct xgene_enet_pdata*) ; 
 int /*<<< orphan*/  xgene_sgmac_set_mac_addr (struct xgene_enet_pdata*) ; 
 int /*<<< orphan*/  xgene_sgmac_set_speed (struct xgene_enet_pdata*) ; 
 int /*<<< orphan*/  xgene_sgmii_enable_autoneg (struct xgene_enet_pdata*) ; 

__attribute__((used)) static void xgene_sgmac_init(struct xgene_enet_pdata *p)
{
	u32 pause_thres_reg, pause_off_thres_reg;
	u32 enet_spare_cfg_reg, rsif_config_reg;
	u32 cfg_bypass_reg, rx_dv_gate_reg;
	u32 data, data1, data2, offset;
	u32 multi_dpf_reg;

	if (!(p->enet_id == XGENE_ENET2 && p->mdio_driver))
		xgene_sgmac_reset(p);

	xgene_sgmii_enable_autoneg(p);
	xgene_sgmac_set_speed(p);
	xgene_sgmac_set_mac_addr(p);

	if (p->enet_id == XGENE_ENET1) {
		enet_spare_cfg_reg = ENET_SPARE_CFG_REG_ADDR;
		rsif_config_reg = RSIF_CONFIG_REG_ADDR;
		cfg_bypass_reg = CFG_BYPASS_ADDR;
		offset = p->port_id * OFFSET_4;
		rx_dv_gate_reg = SG_RX_DV_GATE_REG_0_ADDR + offset;
	} else {
		enet_spare_cfg_reg = XG_ENET_SPARE_CFG_REG_ADDR;
		rsif_config_reg = XG_RSIF_CONFIG_REG_ADDR;
		cfg_bypass_reg = XG_CFG_BYPASS_ADDR;
		rx_dv_gate_reg = XG_MCX_RX_DV_GATE_REG_0_ADDR;
	}

	data = xgene_enet_rd_csr(p, enet_spare_cfg_reg);
	data |= MPA_IDLE_WITH_QMI_EMPTY;
	xgene_enet_wr_csr(p, enet_spare_cfg_reg, data);

	/* Adjust MDC clock frequency */
	data = xgene_enet_rd_mac(p, MII_MGMT_CONFIG_ADDR);
	MGMT_CLOCK_SEL_SET(&data, 7);
	xgene_enet_wr_mac(p, MII_MGMT_CONFIG_ADDR, data);

	/* Enable drop if bufpool not available */
	data = xgene_enet_rd_csr(p, rsif_config_reg);
	data |= CFG_RSIF_FPBUFF_TIMEOUT_EN;
	xgene_enet_wr_csr(p, rsif_config_reg, data);

	/* Configure HW pause frame generation */
	multi_dpf_reg = (p->enet_id == XGENE_ENET1) ? CSR_MULTI_DPF0_ADDR :
			 XG_MCX_MULTI_DPF0_ADDR;
	data = xgene_enet_rd_mcx_csr(p, multi_dpf_reg);
	data = (DEF_QUANTA << 16) | (data & 0xffff);
	xgene_enet_wr_mcx_csr(p, multi_dpf_reg, data);

	if (p->enet_id != XGENE_ENET1) {
		data = xgene_enet_rd_mcx_csr(p, XG_MCX_MULTI_DPF1_ADDR);
		data =  (NORM_PAUSE_OPCODE << 16) | (data & 0xFFFF);
		xgene_enet_wr_mcx_csr(p, XG_MCX_MULTI_DPF1_ADDR, data);
	}

	pause_thres_reg = (p->enet_id == XGENE_ENET1) ? RXBUF_PAUSE_THRESH :
			   XG_RXBUF_PAUSE_THRESH;
	pause_off_thres_reg = (p->enet_id == XGENE_ENET1) ?
			       RXBUF_PAUSE_OFF_THRESH : 0;

	if (p->enet_id == XGENE_ENET1) {
		data1 = xgene_enet_rd_csr(p, pause_thres_reg);
		data2 = xgene_enet_rd_csr(p, pause_off_thres_reg);

		if (!(p->port_id % 2)) {
			data1 = (data1 & 0xffff0000) | DEF_PAUSE_THRES;
			data2 = (data2 & 0xffff0000) | DEF_PAUSE_OFF_THRES;
		} else {
			data1 = (data1 & 0xffff) | (DEF_PAUSE_THRES << 16);
			data2 = (data2 & 0xffff) | (DEF_PAUSE_OFF_THRES << 16);
		}

		xgene_enet_wr_csr(p, pause_thres_reg, data1);
		xgene_enet_wr_csr(p, pause_off_thres_reg, data2);
	} else {
		data = (DEF_PAUSE_OFF_THRES << 16) | DEF_PAUSE_THRES;
		xgene_enet_wr_csr(p, pause_thres_reg, data);
	}

	xgene_sgmac_flowctl_tx(p, p->tx_pause);
	xgene_sgmac_flowctl_rx(p, p->rx_pause);

	/* Bypass traffic gating */
	xgene_enet_wr_csr(p, XG_ENET_SPARE_CFG_REG_1_ADDR, 0x84);
	xgene_enet_wr_csr(p, cfg_bypass_reg, RESUME_TX);
	xgene_enet_wr_mcx_csr(p, rx_dv_gate_reg, RESUME_RX0);
}