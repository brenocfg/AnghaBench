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
struct xgene_enet_pdata {int /*<<< orphan*/  rx_pause; int /*<<< orphan*/  tx_pause; int /*<<< orphan*/  mdio_driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG_BYPASS_ADDR ; 
 int /*<<< orphan*/  CFG_LINK_AGGR_RESUME_0_ADDR ; 
 int CFG_RSIF_FPBUFF_TIMEOUT_EN ; 
 int /*<<< orphan*/  CSR_MULTI_DPF0_ADDR ; 
 int DEF_PAUSE_OFF_THRES ; 
 int DEF_PAUSE_THRES ; 
 int DEF_QUANTA ; 
 int /*<<< orphan*/  MGMT_CLOCK_SEL_SET (int*,int) ; 
 int /*<<< orphan*/  MII_MGMT_CONFIG_ADDR ; 
 int RESUME_RX0 ; 
 int RESUME_TX ; 
 int /*<<< orphan*/  RSIF_CONFIG_REG_ADDR ; 
 int /*<<< orphan*/  RSIF_RAM_DBG_REG0_ADDR ; 
 int /*<<< orphan*/  RXBUF_PAUSE_OFF_THRESH ; 
 int /*<<< orphan*/  RXBUF_PAUSE_THRESH ; 
 int RX_DV_GATE_EN0 ; 
 int /*<<< orphan*/  RX_DV_GATE_REG_0_ADDR ; 
 int TX_DV_GATE_EN0 ; 
 int TX_PORT0 ; 
 int /*<<< orphan*/  xgene_enet_rd_csr (struct xgene_enet_pdata*,int /*<<< orphan*/ ,int*) ; 
 int xgene_enet_rd_mac (struct xgene_enet_pdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgene_enet_rd_mcx_csr (struct xgene_enet_pdata*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  xgene_enet_wr_csr (struct xgene_enet_pdata*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xgene_enet_wr_mac (struct xgene_enet_pdata*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xgene_enet_wr_mcx_csr (struct xgene_enet_pdata*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xgene_gmac_flowctl_rx (struct xgene_enet_pdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgene_gmac_flowctl_tx (struct xgene_enet_pdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgene_gmac_reset (struct xgene_enet_pdata*) ; 
 int /*<<< orphan*/  xgene_gmac_set_mac_addr (struct xgene_enet_pdata*) ; 
 int /*<<< orphan*/  xgene_gmac_set_speed (struct xgene_enet_pdata*) ; 

__attribute__((used)) static void xgene_gmac_init(struct xgene_enet_pdata *pdata)
{
	u32 value;

	if (!pdata->mdio_driver)
		xgene_gmac_reset(pdata);

	xgene_gmac_set_speed(pdata);
	xgene_gmac_set_mac_addr(pdata);

	/* Adjust MDC clock frequency */
	value = xgene_enet_rd_mac(pdata, MII_MGMT_CONFIG_ADDR);
	MGMT_CLOCK_SEL_SET(&value, 7);
	xgene_enet_wr_mac(pdata, MII_MGMT_CONFIG_ADDR, value);

	/* Enable drop if bufpool not available */
	xgene_enet_rd_csr(pdata, RSIF_CONFIG_REG_ADDR, &value);
	value |= CFG_RSIF_FPBUFF_TIMEOUT_EN;
	xgene_enet_wr_csr(pdata, RSIF_CONFIG_REG_ADDR, value);

	/* Rtype should be copied from FP */
	xgene_enet_wr_csr(pdata, RSIF_RAM_DBG_REG0_ADDR, 0);

	/* Configure HW pause frame generation */
	xgene_enet_rd_mcx_csr(pdata, CSR_MULTI_DPF0_ADDR, &value);
	value = (DEF_QUANTA << 16) | (value & 0xFFFF);
	xgene_enet_wr_mcx_csr(pdata, CSR_MULTI_DPF0_ADDR, value);

	xgene_enet_wr_csr(pdata, RXBUF_PAUSE_THRESH, DEF_PAUSE_THRES);
	xgene_enet_wr_csr(pdata, RXBUF_PAUSE_OFF_THRESH, DEF_PAUSE_OFF_THRES);

	xgene_gmac_flowctl_tx(pdata, pdata->tx_pause);
	xgene_gmac_flowctl_rx(pdata, pdata->rx_pause);

	/* Rx-Tx traffic resume */
	xgene_enet_wr_csr(pdata, CFG_LINK_AGGR_RESUME_0_ADDR, TX_PORT0);

	xgene_enet_rd_mcx_csr(pdata, RX_DV_GATE_REG_0_ADDR, &value);
	value &= ~TX_DV_GATE_EN0;
	value &= ~RX_DV_GATE_EN0;
	value |= RESUME_RX0;
	xgene_enet_wr_mcx_csr(pdata, RX_DV_GATE_REG_0_ADDR, value);

	xgene_enet_wr_csr(pdata, CFG_BYPASS_ADDR, RESUME_TX);
}