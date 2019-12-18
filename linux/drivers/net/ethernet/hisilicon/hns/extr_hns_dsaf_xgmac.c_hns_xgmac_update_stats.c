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
struct mac_hw_stats {void* rx_fcs_err; void* rx_symbol_err; void* rx_1731_pkts; void* tx_bad_to_sw; void* tx_good_to_sw; void* rx_unknown_ctrl; void* rx_pfc_tc7; void* rx_pfc_tc6; void* rx_pfc_tc5; void* rx_pfc_tc4; void* rx_pfc_tc3; void* rx_pfc_tc2; void* rx_pfc_tc1; void* rx_pfc_tc0; void* rx_bc_pkts; void* rx_mc_pkts; void* rx_uc_pkts; void* rx_total_bytes; void* rx_total_pkts; void* rx_good_bytes; void* rx_good_pkts; void* rx_jabber_err; void* rx_oversize; void* rx_1519tomax_good; void* rx_1519tomax; void* rx_1024to1518; void* rx_512to1023; void* rx_256to511; void* rx_128to255; void* rx_65to127; void* rx_64bytes; void* rx_under_min; void* rx_undersize; void* rx_fragment_err; void* tx_bad_pkts; void* rx_bad_from_sw; void* rx_good_from_sw; void* tx_1588_pkts; void* tx_1731_pkts; void* tx_ctrl; void* tx_pfc_tc7; void* tx_pfc_tc6; void* tx_pfc_tc5; void* tx_pfc_tc4; void* tx_pfc_tc3; void* tx_pfc_tc2; void* tx_pfc_tc1; void* tx_pfc_tc0; void* tx_bc_pkts; void* tx_mc_pkts; void* tx_uc_pkts; void* tx_total_bytes; void* tx_total_pkts; void* tx_good_bytes; void* tx_good_pkts; void* tx_jabber_err; void* tx_oversize; void* tx_1519tomax_good; void* tx_1519tomax; void* tx_1024to1518; void* tx_512to1023; void* tx_256to511; void* tx_128to255; void* tx_65to127; void* tx_64bytes; void* tx_under_min_pkts; void* tx_undersize; void* tx_fragment_err; } ;
struct mac_driver {TYPE_1__* mac_cb; } ;
struct TYPE_2__ {struct mac_hw_stats hw_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  XGMAC_RX_1731PKTS ; 
 int /*<<< orphan*/  XGMAC_RX_BROADCASTPKTS ; 
 int /*<<< orphan*/  XGMAC_RX_FCSERRPKTS ; 
 int /*<<< orphan*/  XGMAC_RX_FROMAPPBADPKTS ; 
 int /*<<< orphan*/  XGMAC_RX_FROMAPPGOODPKTS ; 
 int /*<<< orphan*/  XGMAC_RX_GOODOCTETS ; 
 int /*<<< orphan*/  XGMAC_RX_GOODPKTS ; 
 int /*<<< orphan*/  XGMAC_RX_MACCTRLPKTS ; 
 int /*<<< orphan*/  XGMAC_RX_MULTICASTPKTS ; 
 int /*<<< orphan*/  XGMAC_RX_PKTSUNDERSIZE ; 
 int /*<<< orphan*/  XGMAC_RX_PKTS_1024TO1518OCTETS ; 
 int /*<<< orphan*/  XGMAC_RX_PKTS_128TO255OCTETS ; 
 int /*<<< orphan*/  XGMAC_RX_PKTS_1519TOMAXOCTETS ; 
 int /*<<< orphan*/  XGMAC_RX_PKTS_1519TOMAXOCTETSOK ; 
 int /*<<< orphan*/  XGMAC_RX_PKTS_256TO511OCTETS ; 
 int /*<<< orphan*/  XGMAC_RX_PKTS_512TO1023OCTETS ; 
 int /*<<< orphan*/  XGMAC_RX_PKTS_64OCTETS ; 
 int /*<<< orphan*/  XGMAC_RX_PKTS_65TO127OCTETS ; 
 int /*<<< orphan*/  XGMAC_RX_PKTS_FRAGMENT ; 
 int /*<<< orphan*/  XGMAC_RX_PKTS_JABBER ; 
 int /*<<< orphan*/  XGMAC_RX_PKTS_OVERSIZE ; 
 int /*<<< orphan*/  XGMAC_RX_PKTS_UNDERMIN ; 
 int /*<<< orphan*/  XGMAC_RX_PRI0PAUSEPKTS ; 
 int /*<<< orphan*/  XGMAC_RX_PRI1PAUSEPKTS ; 
 int /*<<< orphan*/  XGMAC_RX_PRI2PAUSEPKTS ; 
 int /*<<< orphan*/  XGMAC_RX_PRI3PAUSEPKTS ; 
 int /*<<< orphan*/  XGMAC_RX_PRI4PAUSEPKTS ; 
 int /*<<< orphan*/  XGMAC_RX_PRI5PAUSEPKTS ; 
 int /*<<< orphan*/  XGMAC_RX_PRI6PAUSEPKTS ; 
 int /*<<< orphan*/  XGMAC_RX_PRI7PAUSEPKTS ; 
 int /*<<< orphan*/  XGMAC_RX_SYMBOLERRPKTS ; 
 int /*<<< orphan*/  XGMAC_RX_TOTALOCTETS ; 
 int /*<<< orphan*/  XGMAC_RX_TOTAL_PKTS ; 
 int /*<<< orphan*/  XGMAC_RX_UNICASTPKTS ; 
 int /*<<< orphan*/  XGMAC_TX_1588PKTS ; 
 int /*<<< orphan*/  XGMAC_TX_1731PKTS ; 
 int /*<<< orphan*/  XGMAC_TX_BROADCASTPKTS ; 
 int /*<<< orphan*/  XGMAC_TX_ERRALLPKTS ; 
 int /*<<< orphan*/  XGMAC_TX_GOODOCTETS ; 
 int /*<<< orphan*/  XGMAC_TX_GOODPKTS ; 
 int /*<<< orphan*/  XGMAC_TX_MACCTRLPKTS ; 
 int /*<<< orphan*/  XGMAC_TX_MULTICASTPKTS ; 
 int /*<<< orphan*/  XGMAC_TX_PKTS_1024TO1518OCTETS ; 
 int /*<<< orphan*/  XGMAC_TX_PKTS_128TO255OCTETS ; 
 int /*<<< orphan*/  XGMAC_TX_PKTS_1519TOMAXOCTETS ; 
 int /*<<< orphan*/  XGMAC_TX_PKTS_1519TOMAXOCTETSOK ; 
 int /*<<< orphan*/  XGMAC_TX_PKTS_256TO511OCTETS ; 
 int /*<<< orphan*/  XGMAC_TX_PKTS_512TO1023OCTETS ; 
 int /*<<< orphan*/  XGMAC_TX_PKTS_64OCTETS ; 
 int /*<<< orphan*/  XGMAC_TX_PKTS_65TO127OCTETS ; 
 int /*<<< orphan*/  XGMAC_TX_PKTS_FRAGMENT ; 
 int /*<<< orphan*/  XGMAC_TX_PKTS_JABBER ; 
 int /*<<< orphan*/  XGMAC_TX_PKTS_OVERSIZE ; 
 int /*<<< orphan*/  XGMAC_TX_PKTS_UNDERMIN ; 
 int /*<<< orphan*/  XGMAC_TX_PKTS_UNDERSIZE ; 
 int /*<<< orphan*/  XGMAC_TX_PRI0PAUSEPKTS ; 
 int /*<<< orphan*/  XGMAC_TX_PRI1PAUSEPKTS ; 
 int /*<<< orphan*/  XGMAC_TX_PRI2PAUSEPKTS ; 
 int /*<<< orphan*/  XGMAC_TX_PRI3PAUSEPKTS ; 
 int /*<<< orphan*/  XGMAC_TX_PRI4PAUSEPKTS ; 
 int /*<<< orphan*/  XGMAC_TX_PRI5PAUSEPKTS ; 
 int /*<<< orphan*/  XGMAC_TX_PRI6PAUSEPKTS ; 
 int /*<<< orphan*/  XGMAC_TX_PRI7PAUSEPKTS ; 
 int /*<<< orphan*/  XGMAC_TX_SENDAPPBADPKTS ; 
 int /*<<< orphan*/  XGMAC_TX_SENDAPPGOODPKTS ; 
 int /*<<< orphan*/  XGMAC_TX_TOTALOCTETS ; 
 int /*<<< orphan*/  XGMAC_TX_TOTAL_PKTS ; 
 int /*<<< orphan*/  XGMAC_TX_UNICASTPKTS ; 
 void* hns_mac_reg_read64 (struct mac_driver*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns_xgmac_update_stats(void *mac_drv)
{
	struct mac_driver *drv = (struct mac_driver *)mac_drv;
	struct mac_hw_stats *hw_stats = &drv->mac_cb->hw_stats;

	/* TX */
	hw_stats->tx_fragment_err
		= hns_mac_reg_read64(drv, XGMAC_TX_PKTS_FRAGMENT);
	hw_stats->tx_undersize
		= hns_mac_reg_read64(drv, XGMAC_TX_PKTS_UNDERSIZE);
	hw_stats->tx_under_min_pkts
		= hns_mac_reg_read64(drv, XGMAC_TX_PKTS_UNDERMIN);
	hw_stats->tx_64bytes = hns_mac_reg_read64(drv, XGMAC_TX_PKTS_64OCTETS);
	hw_stats->tx_65to127
		= hns_mac_reg_read64(drv, XGMAC_TX_PKTS_65TO127OCTETS);
	hw_stats->tx_128to255
		= hns_mac_reg_read64(drv, XGMAC_TX_PKTS_128TO255OCTETS);
	hw_stats->tx_256to511
		= hns_mac_reg_read64(drv, XGMAC_TX_PKTS_256TO511OCTETS);
	hw_stats->tx_512to1023
		= hns_mac_reg_read64(drv, XGMAC_TX_PKTS_512TO1023OCTETS);
	hw_stats->tx_1024to1518
		= hns_mac_reg_read64(drv, XGMAC_TX_PKTS_1024TO1518OCTETS);
	hw_stats->tx_1519tomax
		= hns_mac_reg_read64(drv, XGMAC_TX_PKTS_1519TOMAXOCTETS);
	hw_stats->tx_1519tomax_good
		= hns_mac_reg_read64(drv, XGMAC_TX_PKTS_1519TOMAXOCTETSOK);
	hw_stats->tx_oversize = hns_mac_reg_read64(drv, XGMAC_TX_PKTS_OVERSIZE);
	hw_stats->tx_jabber_err = hns_mac_reg_read64(drv, XGMAC_TX_PKTS_JABBER);
	hw_stats->tx_good_pkts = hns_mac_reg_read64(drv, XGMAC_TX_GOODPKTS);
	hw_stats->tx_good_bytes = hns_mac_reg_read64(drv, XGMAC_TX_GOODOCTETS);
	hw_stats->tx_total_pkts = hns_mac_reg_read64(drv, XGMAC_TX_TOTAL_PKTS);
	hw_stats->tx_total_bytes
		= hns_mac_reg_read64(drv, XGMAC_TX_TOTALOCTETS);
	hw_stats->tx_uc_pkts = hns_mac_reg_read64(drv, XGMAC_TX_UNICASTPKTS);
	hw_stats->tx_mc_pkts = hns_mac_reg_read64(drv, XGMAC_TX_MULTICASTPKTS);
	hw_stats->tx_bc_pkts = hns_mac_reg_read64(drv, XGMAC_TX_BROADCASTPKTS);
	hw_stats->tx_pfc_tc0 = hns_mac_reg_read64(drv, XGMAC_TX_PRI0PAUSEPKTS);
	hw_stats->tx_pfc_tc1 = hns_mac_reg_read64(drv, XGMAC_TX_PRI1PAUSEPKTS);
	hw_stats->tx_pfc_tc2 = hns_mac_reg_read64(drv, XGMAC_TX_PRI2PAUSEPKTS);
	hw_stats->tx_pfc_tc3 = hns_mac_reg_read64(drv, XGMAC_TX_PRI3PAUSEPKTS);
	hw_stats->tx_pfc_tc4 = hns_mac_reg_read64(drv, XGMAC_TX_PRI4PAUSEPKTS);
	hw_stats->tx_pfc_tc5 = hns_mac_reg_read64(drv, XGMAC_TX_PRI5PAUSEPKTS);
	hw_stats->tx_pfc_tc6 = hns_mac_reg_read64(drv, XGMAC_TX_PRI6PAUSEPKTS);
	hw_stats->tx_pfc_tc7 = hns_mac_reg_read64(drv, XGMAC_TX_PRI7PAUSEPKTS);
	hw_stats->tx_ctrl = hns_mac_reg_read64(drv, XGMAC_TX_MACCTRLPKTS);
	hw_stats->tx_1731_pkts = hns_mac_reg_read64(drv, XGMAC_TX_1731PKTS);
	hw_stats->tx_1588_pkts = hns_mac_reg_read64(drv, XGMAC_TX_1588PKTS);
	hw_stats->rx_good_from_sw
		= hns_mac_reg_read64(drv, XGMAC_RX_FROMAPPGOODPKTS);
	hw_stats->rx_bad_from_sw
		= hns_mac_reg_read64(drv, XGMAC_RX_FROMAPPBADPKTS);
	hw_stats->tx_bad_pkts = hns_mac_reg_read64(drv, XGMAC_TX_ERRALLPKTS);

	/* RX */
	hw_stats->rx_fragment_err
		= hns_mac_reg_read64(drv, XGMAC_RX_PKTS_FRAGMENT);
	hw_stats->rx_undersize
		= hns_mac_reg_read64(drv, XGMAC_RX_PKTSUNDERSIZE);
	hw_stats->rx_under_min
		= hns_mac_reg_read64(drv, XGMAC_RX_PKTS_UNDERMIN);
	hw_stats->rx_64bytes = hns_mac_reg_read64(drv, XGMAC_RX_PKTS_64OCTETS);
	hw_stats->rx_65to127
		= hns_mac_reg_read64(drv, XGMAC_RX_PKTS_65TO127OCTETS);
	hw_stats->rx_128to255
		= hns_mac_reg_read64(drv, XGMAC_RX_PKTS_128TO255OCTETS);
	hw_stats->rx_256to511
		= hns_mac_reg_read64(drv, XGMAC_RX_PKTS_256TO511OCTETS);
	hw_stats->rx_512to1023
		= hns_mac_reg_read64(drv, XGMAC_RX_PKTS_512TO1023OCTETS);
	hw_stats->rx_1024to1518
		= hns_mac_reg_read64(drv, XGMAC_RX_PKTS_1024TO1518OCTETS);
	hw_stats->rx_1519tomax
		= hns_mac_reg_read64(drv, XGMAC_RX_PKTS_1519TOMAXOCTETS);
	hw_stats->rx_1519tomax_good
		= hns_mac_reg_read64(drv, XGMAC_RX_PKTS_1519TOMAXOCTETSOK);
	hw_stats->rx_oversize = hns_mac_reg_read64(drv, XGMAC_RX_PKTS_OVERSIZE);
	hw_stats->rx_jabber_err = hns_mac_reg_read64(drv, XGMAC_RX_PKTS_JABBER);
	hw_stats->rx_good_pkts = hns_mac_reg_read64(drv, XGMAC_RX_GOODPKTS);
	hw_stats->rx_good_bytes = hns_mac_reg_read64(drv, XGMAC_RX_GOODOCTETS);
	hw_stats->rx_total_pkts = hns_mac_reg_read64(drv, XGMAC_RX_TOTAL_PKTS);
	hw_stats->rx_total_bytes
		= hns_mac_reg_read64(drv, XGMAC_RX_TOTALOCTETS);
	hw_stats->rx_uc_pkts = hns_mac_reg_read64(drv, XGMAC_RX_UNICASTPKTS);
	hw_stats->rx_mc_pkts = hns_mac_reg_read64(drv, XGMAC_RX_MULTICASTPKTS);
	hw_stats->rx_bc_pkts = hns_mac_reg_read64(drv, XGMAC_RX_BROADCASTPKTS);
	hw_stats->rx_pfc_tc0 = hns_mac_reg_read64(drv, XGMAC_RX_PRI0PAUSEPKTS);
	hw_stats->rx_pfc_tc1 = hns_mac_reg_read64(drv, XGMAC_RX_PRI1PAUSEPKTS);
	hw_stats->rx_pfc_tc2 = hns_mac_reg_read64(drv, XGMAC_RX_PRI2PAUSEPKTS);
	hw_stats->rx_pfc_tc3 = hns_mac_reg_read64(drv, XGMAC_RX_PRI3PAUSEPKTS);
	hw_stats->rx_pfc_tc4 = hns_mac_reg_read64(drv, XGMAC_RX_PRI4PAUSEPKTS);
	hw_stats->rx_pfc_tc5 = hns_mac_reg_read64(drv, XGMAC_RX_PRI5PAUSEPKTS);
	hw_stats->rx_pfc_tc6 = hns_mac_reg_read64(drv, XGMAC_RX_PRI6PAUSEPKTS);
	hw_stats->rx_pfc_tc7 = hns_mac_reg_read64(drv, XGMAC_RX_PRI7PAUSEPKTS);

	hw_stats->rx_unknown_ctrl
		= hns_mac_reg_read64(drv, XGMAC_RX_MACCTRLPKTS);
	hw_stats->tx_good_to_sw
		= hns_mac_reg_read64(drv, XGMAC_TX_SENDAPPGOODPKTS);
	hw_stats->tx_bad_to_sw
		= hns_mac_reg_read64(drv, XGMAC_TX_SENDAPPBADPKTS);
	hw_stats->rx_1731_pkts = hns_mac_reg_read64(drv, XGMAC_RX_1731PKTS);
	hw_stats->rx_symbol_err
		= hns_mac_reg_read64(drv, XGMAC_RX_SYMBOLERRPKTS);
	hw_stats->rx_fcs_err = hns_mac_reg_read64(drv, XGMAC_RX_FCSERRPKTS);
}