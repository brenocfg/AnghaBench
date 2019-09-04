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
struct mac_hw_stats {int /*<<< orphan*/  tx_pfc_tc0; int /*<<< orphan*/  tx_crc_err; int /*<<< orphan*/  tx_vlan; int /*<<< orphan*/  tx_underrun_err; int /*<<< orphan*/  tx_jabber_err; int /*<<< orphan*/  tx_1519tomax; int /*<<< orphan*/  tx_1024to1518; int /*<<< orphan*/  tx_512to1023; int /*<<< orphan*/  tx_256to511; int /*<<< orphan*/  tx_128to255; int /*<<< orphan*/  tx_65to127; int /*<<< orphan*/  tx_64bytes; int /*<<< orphan*/  tx_bc_pkts; int /*<<< orphan*/  tx_mc_pkts; int /*<<< orphan*/  tx_uc_pkts; int /*<<< orphan*/  tx_bad_bytes; int /*<<< orphan*/  tx_good_bytes; int /*<<< orphan*/  rx_comma_err; int /*<<< orphan*/  rx_len_err; int /*<<< orphan*/  rx_fifo_overrun_err; int /*<<< orphan*/  rx_filter_bytes; int /*<<< orphan*/  rx_filter_pkts; int /*<<< orphan*/  rx_under_min; int /*<<< orphan*/  rx_minto64; int /*<<< orphan*/  rx_long_err; int /*<<< orphan*/  rx_unknown_ctrl; int /*<<< orphan*/  rx_pfc_tc0; int /*<<< orphan*/  rx_jabber_err; int /*<<< orphan*/  rx_oversize; int /*<<< orphan*/  rx_align_err; int /*<<< orphan*/  rx_data_err; int /*<<< orphan*/  rx_vlan_pkts; int /*<<< orphan*/  rx_fcs_err; int /*<<< orphan*/  rx_1519tomax; int /*<<< orphan*/  rx_1024to1518; int /*<<< orphan*/  rx_512to1023; int /*<<< orphan*/  rx_256to511; int /*<<< orphan*/  rx_128to255; int /*<<< orphan*/  rx_65to127; int /*<<< orphan*/  rx_64bytes; int /*<<< orphan*/  rx_bc_pkts; int /*<<< orphan*/  rx_mc_pkts; int /*<<< orphan*/  rx_uc_pkts; int /*<<< orphan*/  rx_bad_bytes; int /*<<< orphan*/  rx_good_bytes; } ;
struct mac_driver {TYPE_1__* mac_cb; } ;
struct TYPE_2__ {struct mac_hw_stats hw_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  GMAC_OCTETS_TRANSMITTED_BAD_REG ; 
 int /*<<< orphan*/  GMAC_OCTETS_TRANSMITTED_OK_REG ; 
 int /*<<< orphan*/  GMAC_RX_ALIGN_ERRORS_REG ; 
 int /*<<< orphan*/  GMAC_RX_BC_PKTS_REG ; 
 int /*<<< orphan*/  GMAC_RX_DATA_ERR_REG ; 
 int /*<<< orphan*/  GMAC_RX_FAIL_COMMA_CNT_REG ; 
 int /*<<< orphan*/  GMAC_RX_FCS_ERRORS_REG ; 
 int /*<<< orphan*/  GMAC_RX_FILT_PKT_CNT_REG ; 
 int /*<<< orphan*/  GMAC_RX_JABBER_ERRORS_REG ; 
 int /*<<< orphan*/  GMAC_RX_LENGTHFIELD_ERR_CNT_REG ; 
 int /*<<< orphan*/  GMAC_RX_LONG_ERRORS_REG ; 
 int /*<<< orphan*/  GMAC_RX_MC_PKTS_REG ; 
 int /*<<< orphan*/  GMAC_RX_OCTETS_BAD_REG ; 
 int /*<<< orphan*/  GMAC_RX_OCTETS_TOTAL_FILT_REG ; 
 int /*<<< orphan*/  GMAC_RX_OCTETS_TOTAL_OK_REG ; 
 int /*<<< orphan*/  GMAC_RX_OVERRUN_CNT_REG ; 
 int /*<<< orphan*/  GMAC_RX_PAUSE_MACCTRL_FRAM_REG ; 
 int /*<<< orphan*/  GMAC_RX_PKTS_1024TO1518OCTETS_REG ; 
 int /*<<< orphan*/  GMAC_RX_PKTS_128TO255OCTETS_REG ; 
 int /*<<< orphan*/  GMAC_RX_PKTS_1519TOMAXOCTETS_REG ; 
 int /*<<< orphan*/  GMAC_RX_PKTS_255TO511OCTETS_REG ; 
 int /*<<< orphan*/  GMAC_RX_PKTS_512TO1023OCTETS_REG ; 
 int /*<<< orphan*/  GMAC_RX_PKTS_64OCTETS_REG ; 
 int /*<<< orphan*/  GMAC_RX_PKTS_65TO127OCTETS_REG ; 
 int /*<<< orphan*/  GMAC_RX_RUNT_ERR_CNT_REG ; 
 int /*<<< orphan*/  GMAC_RX_SHORT_ERR_CNT_REG ; 
 int /*<<< orphan*/  GMAC_RX_TAGGED_REG ; 
 int /*<<< orphan*/  GMAC_RX_UC_PKTS_REG ; 
 int /*<<< orphan*/  GMAC_RX_UNKNOWN_MACCTRL_FRAM_REG ; 
 int /*<<< orphan*/  GMAC_RX_VERY_LONG_ERR_CNT_REG ; 
 int /*<<< orphan*/  GMAC_TX_BC_PKTS_REG ; 
 int /*<<< orphan*/  GMAC_TX_CRC_ERROR_REG ; 
 int /*<<< orphan*/  GMAC_TX_EXCESSIVE_LENGTH_DROP_REG ; 
 int /*<<< orphan*/  GMAC_TX_MC_PKTS_REG ; 
 int /*<<< orphan*/  GMAC_TX_PAUSE_FRAMES_REG ; 
 int /*<<< orphan*/  GMAC_TX_PKTS_1024TO1518OCTETS_REG ; 
 int /*<<< orphan*/  GMAC_TX_PKTS_128TO255OCTETS_REG ; 
 int /*<<< orphan*/  GMAC_TX_PKTS_1519TOMAXOCTETS_REG ; 
 int /*<<< orphan*/  GMAC_TX_PKTS_255TO511OCTETS_REG ; 
 int /*<<< orphan*/  GMAC_TX_PKTS_512TO1023OCTETS_REG ; 
 int /*<<< orphan*/  GMAC_TX_PKTS_64OCTETS_REG ; 
 int /*<<< orphan*/  GMAC_TX_PKTS_65TO127OCTETS_REG ; 
 int /*<<< orphan*/  GMAC_TX_TAGGED_REG ; 
 int /*<<< orphan*/  GMAC_TX_UC_PKTS_REG ; 
 int /*<<< orphan*/  GMAC_TX_UNDERRUN_REG ; 
 scalar_t__ dsaf_read_dev (struct mac_driver*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns_gmac_update_stats(void *mac_drv)
{
	struct mac_hw_stats *hw_stats = NULL;
	struct mac_driver *drv = (struct mac_driver *)mac_drv;

	hw_stats = &drv->mac_cb->hw_stats;

	/* RX */
	hw_stats->rx_good_bytes
		+= dsaf_read_dev(drv, GMAC_RX_OCTETS_TOTAL_OK_REG);
	hw_stats->rx_bad_bytes
		+= dsaf_read_dev(drv, GMAC_RX_OCTETS_BAD_REG);
	hw_stats->rx_uc_pkts += dsaf_read_dev(drv, GMAC_RX_UC_PKTS_REG);
	hw_stats->rx_mc_pkts += dsaf_read_dev(drv, GMAC_RX_MC_PKTS_REG);
	hw_stats->rx_bc_pkts += dsaf_read_dev(drv, GMAC_RX_BC_PKTS_REG);
	hw_stats->rx_64bytes
		+= dsaf_read_dev(drv, GMAC_RX_PKTS_64OCTETS_REG);
	hw_stats->rx_65to127
		+= dsaf_read_dev(drv, GMAC_RX_PKTS_65TO127OCTETS_REG);
	hw_stats->rx_128to255
		+= dsaf_read_dev(drv, GMAC_RX_PKTS_128TO255OCTETS_REG);
	hw_stats->rx_256to511
		+= dsaf_read_dev(drv, GMAC_RX_PKTS_255TO511OCTETS_REG);
	hw_stats->rx_512to1023
		+= dsaf_read_dev(drv, GMAC_RX_PKTS_512TO1023OCTETS_REG);
	hw_stats->rx_1024to1518
		+= dsaf_read_dev(drv, GMAC_RX_PKTS_1024TO1518OCTETS_REG);
	hw_stats->rx_1519tomax
		+= dsaf_read_dev(drv, GMAC_RX_PKTS_1519TOMAXOCTETS_REG);
	hw_stats->rx_fcs_err += dsaf_read_dev(drv, GMAC_RX_FCS_ERRORS_REG);
	hw_stats->rx_vlan_pkts += dsaf_read_dev(drv, GMAC_RX_TAGGED_REG);
	hw_stats->rx_data_err += dsaf_read_dev(drv, GMAC_RX_DATA_ERR_REG);
	hw_stats->rx_align_err
		+= dsaf_read_dev(drv, GMAC_RX_ALIGN_ERRORS_REG);
	hw_stats->rx_oversize
		+= dsaf_read_dev(drv, GMAC_RX_LONG_ERRORS_REG);
	hw_stats->rx_jabber_err
		+= dsaf_read_dev(drv, GMAC_RX_JABBER_ERRORS_REG);
	hw_stats->rx_pfc_tc0
		+= dsaf_read_dev(drv, GMAC_RX_PAUSE_MACCTRL_FRAM_REG);
	hw_stats->rx_unknown_ctrl
		+= dsaf_read_dev(drv, GMAC_RX_UNKNOWN_MACCTRL_FRAM_REG);
	hw_stats->rx_long_err
		+= dsaf_read_dev(drv, GMAC_RX_VERY_LONG_ERR_CNT_REG);
	hw_stats->rx_minto64
		+= dsaf_read_dev(drv, GMAC_RX_RUNT_ERR_CNT_REG);
	hw_stats->rx_under_min
		+= dsaf_read_dev(drv, GMAC_RX_SHORT_ERR_CNT_REG);
	hw_stats->rx_filter_pkts
		+= dsaf_read_dev(drv, GMAC_RX_FILT_PKT_CNT_REG);
	hw_stats->rx_filter_bytes
		+= dsaf_read_dev(drv, GMAC_RX_OCTETS_TOTAL_FILT_REG);
	hw_stats->rx_fifo_overrun_err
		+= dsaf_read_dev(drv, GMAC_RX_OVERRUN_CNT_REG);
	hw_stats->rx_len_err
		+= dsaf_read_dev(drv, GMAC_RX_LENGTHFIELD_ERR_CNT_REG);
	hw_stats->rx_comma_err
		+= dsaf_read_dev(drv, GMAC_RX_FAIL_COMMA_CNT_REG);

	/* TX */
	hw_stats->tx_good_bytes
		+= dsaf_read_dev(drv, GMAC_OCTETS_TRANSMITTED_OK_REG);
	hw_stats->tx_bad_bytes
		+= dsaf_read_dev(drv, GMAC_OCTETS_TRANSMITTED_BAD_REG);
	hw_stats->tx_uc_pkts += dsaf_read_dev(drv, GMAC_TX_UC_PKTS_REG);
	hw_stats->tx_mc_pkts += dsaf_read_dev(drv, GMAC_TX_MC_PKTS_REG);
	hw_stats->tx_bc_pkts += dsaf_read_dev(drv, GMAC_TX_BC_PKTS_REG);
	hw_stats->tx_64bytes
		+= dsaf_read_dev(drv, GMAC_TX_PKTS_64OCTETS_REG);
	hw_stats->tx_65to127
		+= dsaf_read_dev(drv, GMAC_TX_PKTS_65TO127OCTETS_REG);
	hw_stats->tx_128to255
		+= dsaf_read_dev(drv, GMAC_TX_PKTS_128TO255OCTETS_REG);
	hw_stats->tx_256to511
		+= dsaf_read_dev(drv, GMAC_TX_PKTS_255TO511OCTETS_REG);
	hw_stats->tx_512to1023
		+= dsaf_read_dev(drv, GMAC_TX_PKTS_512TO1023OCTETS_REG);
	hw_stats->tx_1024to1518
		+= dsaf_read_dev(drv, GMAC_TX_PKTS_1024TO1518OCTETS_REG);
	hw_stats->tx_1519tomax
		+= dsaf_read_dev(drv, GMAC_TX_PKTS_1519TOMAXOCTETS_REG);
	hw_stats->tx_jabber_err
		+= dsaf_read_dev(drv, GMAC_TX_EXCESSIVE_LENGTH_DROP_REG);
	hw_stats->tx_underrun_err
		+= dsaf_read_dev(drv, GMAC_TX_UNDERRUN_REG);
	hw_stats->tx_vlan += dsaf_read_dev(drv, GMAC_TX_TAGGED_REG);
	hw_stats->tx_crc_err += dsaf_read_dev(drv, GMAC_TX_CRC_ERROR_REG);
	hw_stats->tx_pfc_tc0
		+= dsaf_read_dev(drv, GMAC_TX_PAUSE_FRAMES_REG);
}