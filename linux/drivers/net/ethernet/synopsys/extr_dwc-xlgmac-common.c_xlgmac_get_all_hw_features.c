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
struct xlgmac_hw_features {int dma_width; int hash_table_size; void* tc_cnt; void* tx_ch_cnt; void* rx_ch_cnt; void* tx_q_cnt; void* rx_q_cnt; void* aux_snap_num; void* pps_out_num; void* l3l4_filter_num; void* rss; void* dma_debug; void* tso; void* sph; void* dcb; void* adv_ts_hi; void* tx_fifo_size; void* rx_fifo_size; void* sa_vlan_ins; void* ts_src; void* addn_mac; void* rx_coe; void* tx_coe; void* eee; void* ts; void* aoe; void* mmc; void* mgk; void* rwk; void* sma; void* vlhash; void* phyifsel; void* version; } ;
struct xlgmac_pdata {scalar_t__ mac_regs; struct xlgmac_hw_features hw_feat; } ;

/* Variables and functions */
 scalar_t__ MAC_HWF0R ; 
 int /*<<< orphan*/  MAC_HWF0R_ADDMACADRSEL_LEN ; 
 int /*<<< orphan*/  MAC_HWF0R_ADDMACADRSEL_POS ; 
 int /*<<< orphan*/  MAC_HWF0R_ARPOFFSEL_LEN ; 
 int /*<<< orphan*/  MAC_HWF0R_ARPOFFSEL_POS ; 
 int /*<<< orphan*/  MAC_HWF0R_EEESEL_LEN ; 
 int /*<<< orphan*/  MAC_HWF0R_EEESEL_POS ; 
 int /*<<< orphan*/  MAC_HWF0R_MGKSEL_LEN ; 
 int /*<<< orphan*/  MAC_HWF0R_MGKSEL_POS ; 
 int /*<<< orphan*/  MAC_HWF0R_MMCSEL_LEN ; 
 int /*<<< orphan*/  MAC_HWF0R_MMCSEL_POS ; 
 int /*<<< orphan*/  MAC_HWF0R_PHYIFSEL_LEN ; 
 int /*<<< orphan*/  MAC_HWF0R_PHYIFSEL_POS ; 
 int /*<<< orphan*/  MAC_HWF0R_RWKSEL_LEN ; 
 int /*<<< orphan*/  MAC_HWF0R_RWKSEL_POS ; 
 int /*<<< orphan*/  MAC_HWF0R_RXCOESEL_LEN ; 
 int /*<<< orphan*/  MAC_HWF0R_RXCOESEL_POS ; 
 int /*<<< orphan*/  MAC_HWF0R_SAVLANINS_LEN ; 
 int /*<<< orphan*/  MAC_HWF0R_SAVLANINS_POS ; 
 int /*<<< orphan*/  MAC_HWF0R_SMASEL_LEN ; 
 int /*<<< orphan*/  MAC_HWF0R_SMASEL_POS ; 
 int /*<<< orphan*/  MAC_HWF0R_TSSEL_LEN ; 
 int /*<<< orphan*/  MAC_HWF0R_TSSEL_POS ; 
 int /*<<< orphan*/  MAC_HWF0R_TSSTSSEL_LEN ; 
 int /*<<< orphan*/  MAC_HWF0R_TSSTSSEL_POS ; 
 int /*<<< orphan*/  MAC_HWF0R_TXCOESEL_LEN ; 
 int /*<<< orphan*/  MAC_HWF0R_TXCOESEL_POS ; 
 int /*<<< orphan*/  MAC_HWF0R_VLHASH_LEN ; 
 int /*<<< orphan*/  MAC_HWF0R_VLHASH_POS ; 
 scalar_t__ MAC_HWF1R ; 
 int /*<<< orphan*/  MAC_HWF1R_ADDR64_LEN ; 
 int /*<<< orphan*/  MAC_HWF1R_ADDR64_POS ; 
 int /*<<< orphan*/  MAC_HWF1R_ADVTHWORD_LEN ; 
 int /*<<< orphan*/  MAC_HWF1R_ADVTHWORD_POS ; 
 int /*<<< orphan*/  MAC_HWF1R_DBGMEMA_LEN ; 
 int /*<<< orphan*/  MAC_HWF1R_DBGMEMA_POS ; 
 int /*<<< orphan*/  MAC_HWF1R_DCBEN_LEN ; 
 int /*<<< orphan*/  MAC_HWF1R_DCBEN_POS ; 
 int /*<<< orphan*/  MAC_HWF1R_HASHTBLSZ_LEN ; 
 int /*<<< orphan*/  MAC_HWF1R_HASHTBLSZ_POS ; 
 int /*<<< orphan*/  MAC_HWF1R_L3L4FNUM_LEN ; 
 int /*<<< orphan*/  MAC_HWF1R_L3L4FNUM_POS ; 
 int /*<<< orphan*/  MAC_HWF1R_NUMTC_LEN ; 
 int /*<<< orphan*/  MAC_HWF1R_NUMTC_POS ; 
 int /*<<< orphan*/  MAC_HWF1R_RSSEN_LEN ; 
 int /*<<< orphan*/  MAC_HWF1R_RSSEN_POS ; 
 int /*<<< orphan*/  MAC_HWF1R_RXFIFOSIZE_LEN ; 
 int /*<<< orphan*/  MAC_HWF1R_RXFIFOSIZE_POS ; 
 int /*<<< orphan*/  MAC_HWF1R_SPHEN_LEN ; 
 int /*<<< orphan*/  MAC_HWF1R_SPHEN_POS ; 
 int /*<<< orphan*/  MAC_HWF1R_TSOEN_LEN ; 
 int /*<<< orphan*/  MAC_HWF1R_TSOEN_POS ; 
 int /*<<< orphan*/  MAC_HWF1R_TXFIFOSIZE_LEN ; 
 int /*<<< orphan*/  MAC_HWF1R_TXFIFOSIZE_POS ; 
 scalar_t__ MAC_HWF2R ; 
 int /*<<< orphan*/  MAC_HWF2R_AUXSNAPNUM_LEN ; 
 int /*<<< orphan*/  MAC_HWF2R_AUXSNAPNUM_POS ; 
 int /*<<< orphan*/  MAC_HWF2R_PPSOUTNUM_LEN ; 
 int /*<<< orphan*/  MAC_HWF2R_PPSOUTNUM_POS ; 
 int /*<<< orphan*/  MAC_HWF2R_RXCHCNT_LEN ; 
 int /*<<< orphan*/  MAC_HWF2R_RXCHCNT_POS ; 
 int /*<<< orphan*/  MAC_HWF2R_RXQCNT_LEN ; 
 int /*<<< orphan*/  MAC_HWF2R_RXQCNT_POS ; 
 int /*<<< orphan*/  MAC_HWF2R_TXCHCNT_LEN ; 
 int /*<<< orphan*/  MAC_HWF2R_TXCHCNT_POS ; 
 int /*<<< orphan*/  MAC_HWF2R_TXQCNT_LEN ; 
 int /*<<< orphan*/  MAC_HWF2R_TXQCNT_POS ; 
 scalar_t__ MAC_VR ; 
 void* XLGMAC_GET_REG_BITS (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct xlgmac_hw_features*,int /*<<< orphan*/ ,int) ; 
 void* readl (scalar_t__) ; 

void xlgmac_get_all_hw_features(struct xlgmac_pdata *pdata)
{
	struct xlgmac_hw_features *hw_feat = &pdata->hw_feat;
	unsigned int mac_hfr0, mac_hfr1, mac_hfr2;

	mac_hfr0 = readl(pdata->mac_regs + MAC_HWF0R);
	mac_hfr1 = readl(pdata->mac_regs + MAC_HWF1R);
	mac_hfr2 = readl(pdata->mac_regs + MAC_HWF2R);

	memset(hw_feat, 0, sizeof(*hw_feat));

	hw_feat->version = readl(pdata->mac_regs + MAC_VR);

	/* Hardware feature register 0 */
	hw_feat->phyifsel    = XLGMAC_GET_REG_BITS(mac_hfr0,
						MAC_HWF0R_PHYIFSEL_POS,
						MAC_HWF0R_PHYIFSEL_LEN);
	hw_feat->vlhash      = XLGMAC_GET_REG_BITS(mac_hfr0,
						MAC_HWF0R_VLHASH_POS,
						MAC_HWF0R_VLHASH_LEN);
	hw_feat->sma         = XLGMAC_GET_REG_BITS(mac_hfr0,
						MAC_HWF0R_SMASEL_POS,
						MAC_HWF0R_SMASEL_LEN);
	hw_feat->rwk         = XLGMAC_GET_REG_BITS(mac_hfr0,
						MAC_HWF0R_RWKSEL_POS,
						MAC_HWF0R_RWKSEL_LEN);
	hw_feat->mgk         = XLGMAC_GET_REG_BITS(mac_hfr0,
						MAC_HWF0R_MGKSEL_POS,
						MAC_HWF0R_MGKSEL_LEN);
	hw_feat->mmc         = XLGMAC_GET_REG_BITS(mac_hfr0,
						MAC_HWF0R_MMCSEL_POS,
						MAC_HWF0R_MMCSEL_LEN);
	hw_feat->aoe         = XLGMAC_GET_REG_BITS(mac_hfr0,
						MAC_HWF0R_ARPOFFSEL_POS,
						MAC_HWF0R_ARPOFFSEL_LEN);
	hw_feat->ts          = XLGMAC_GET_REG_BITS(mac_hfr0,
						MAC_HWF0R_TSSEL_POS,
						MAC_HWF0R_TSSEL_LEN);
	hw_feat->eee         = XLGMAC_GET_REG_BITS(mac_hfr0,
						MAC_HWF0R_EEESEL_POS,
						MAC_HWF0R_EEESEL_LEN);
	hw_feat->tx_coe      = XLGMAC_GET_REG_BITS(mac_hfr0,
						MAC_HWF0R_TXCOESEL_POS,
						MAC_HWF0R_TXCOESEL_LEN);
	hw_feat->rx_coe      = XLGMAC_GET_REG_BITS(mac_hfr0,
						MAC_HWF0R_RXCOESEL_POS,
						MAC_HWF0R_RXCOESEL_LEN);
	hw_feat->addn_mac    = XLGMAC_GET_REG_BITS(mac_hfr0,
						MAC_HWF0R_ADDMACADRSEL_POS,
						MAC_HWF0R_ADDMACADRSEL_LEN);
	hw_feat->ts_src      = XLGMAC_GET_REG_BITS(mac_hfr0,
						MAC_HWF0R_TSSTSSEL_POS,
						MAC_HWF0R_TSSTSSEL_LEN);
	hw_feat->sa_vlan_ins = XLGMAC_GET_REG_BITS(mac_hfr0,
						MAC_HWF0R_SAVLANINS_POS,
						MAC_HWF0R_SAVLANINS_LEN);

	/* Hardware feature register 1 */
	hw_feat->rx_fifo_size  = XLGMAC_GET_REG_BITS(mac_hfr1,
						MAC_HWF1R_RXFIFOSIZE_POS,
						MAC_HWF1R_RXFIFOSIZE_LEN);
	hw_feat->tx_fifo_size  = XLGMAC_GET_REG_BITS(mac_hfr1,
						MAC_HWF1R_TXFIFOSIZE_POS,
						MAC_HWF1R_TXFIFOSIZE_LEN);
	hw_feat->adv_ts_hi     = XLGMAC_GET_REG_BITS(mac_hfr1,
						MAC_HWF1R_ADVTHWORD_POS,
						MAC_HWF1R_ADVTHWORD_LEN);
	hw_feat->dma_width     = XLGMAC_GET_REG_BITS(mac_hfr1,
						MAC_HWF1R_ADDR64_POS,
						MAC_HWF1R_ADDR64_LEN);
	hw_feat->dcb           = XLGMAC_GET_REG_BITS(mac_hfr1,
						MAC_HWF1R_DCBEN_POS,
						MAC_HWF1R_DCBEN_LEN);
	hw_feat->sph           = XLGMAC_GET_REG_BITS(mac_hfr1,
						MAC_HWF1R_SPHEN_POS,
						MAC_HWF1R_SPHEN_LEN);
	hw_feat->tso           = XLGMAC_GET_REG_BITS(mac_hfr1,
						MAC_HWF1R_TSOEN_POS,
						MAC_HWF1R_TSOEN_LEN);
	hw_feat->dma_debug     = XLGMAC_GET_REG_BITS(mac_hfr1,
						MAC_HWF1R_DBGMEMA_POS,
						MAC_HWF1R_DBGMEMA_LEN);
	hw_feat->rss           = XLGMAC_GET_REG_BITS(mac_hfr1,
						MAC_HWF1R_RSSEN_POS,
						MAC_HWF1R_RSSEN_LEN);
	hw_feat->tc_cnt	       = XLGMAC_GET_REG_BITS(mac_hfr1,
						MAC_HWF1R_NUMTC_POS,
						MAC_HWF1R_NUMTC_LEN);
	hw_feat->hash_table_size = XLGMAC_GET_REG_BITS(mac_hfr1,
						MAC_HWF1R_HASHTBLSZ_POS,
						MAC_HWF1R_HASHTBLSZ_LEN);
	hw_feat->l3l4_filter_num = XLGMAC_GET_REG_BITS(mac_hfr1,
						MAC_HWF1R_L3L4FNUM_POS,
						MAC_HWF1R_L3L4FNUM_LEN);

	/* Hardware feature register 2 */
	hw_feat->rx_q_cnt     = XLGMAC_GET_REG_BITS(mac_hfr2,
						MAC_HWF2R_RXQCNT_POS,
						MAC_HWF2R_RXQCNT_LEN);
	hw_feat->tx_q_cnt     = XLGMAC_GET_REG_BITS(mac_hfr2,
						MAC_HWF2R_TXQCNT_POS,
						MAC_HWF2R_TXQCNT_LEN);
	hw_feat->rx_ch_cnt    = XLGMAC_GET_REG_BITS(mac_hfr2,
						MAC_HWF2R_RXCHCNT_POS,
						MAC_HWF2R_RXCHCNT_LEN);
	hw_feat->tx_ch_cnt    = XLGMAC_GET_REG_BITS(mac_hfr2,
						MAC_HWF2R_TXCHCNT_POS,
						MAC_HWF2R_TXCHCNT_LEN);
	hw_feat->pps_out_num  = XLGMAC_GET_REG_BITS(mac_hfr2,
						MAC_HWF2R_PPSOUTNUM_POS,
						MAC_HWF2R_PPSOUTNUM_LEN);
	hw_feat->aux_snap_num = XLGMAC_GET_REG_BITS(mac_hfr2,
						MAC_HWF2R_AUXSNAPNUM_POS,
						MAC_HWF2R_AUXSNAPNUM_LEN);

	/* Translate the Hash Table size into actual number */
	switch (hw_feat->hash_table_size) {
	case 0:
		break;
	case 1:
		hw_feat->hash_table_size = 64;
		break;
	case 2:
		hw_feat->hash_table_size = 128;
		break;
	case 3:
		hw_feat->hash_table_size = 256;
		break;
	}

	/* Translate the address width setting into actual number */
	switch (hw_feat->dma_width) {
	case 0:
		hw_feat->dma_width = 32;
		break;
	case 1:
		hw_feat->dma_width = 40;
		break;
	case 2:
		hw_feat->dma_width = 48;
		break;
	default:
		hw_feat->dma_width = 32;
	}

	/* The Queue, Channel and TC counts are zero based so increment them
	 * to get the actual number
	 */
	hw_feat->rx_q_cnt++;
	hw_feat->tx_q_cnt++;
	hw_feat->rx_ch_cnt++;
	hw_feat->tx_ch_cnt++;
	hw_feat->tc_cnt++;
}