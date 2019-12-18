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
typedef  void* u8 ;
struct dwc3 {scalar_t__ imod_interval; void* tx_max_burst_prd; void* tx_thr_num_pkt_prd; void* rx_max_burst_prd; void* rx_thr_num_pkt_prd; void* hird_threshold; void* tx_de_emphasis; void* lpm_nyet_threshold; void* dis_metastability_quirk; int /*<<< orphan*/  fladj; int /*<<< orphan*/  hsphy_interface; void* tx_de_emphasis_quirk; void* dis_tx_ipgap_linecheck_quirk; void* dis_del_phy_power_chg_quirk; void* dis_u2_freeclk_exists_quirk; void* dis_rxdet_inp3_quirk; void* dis_u2_entry_quirk; void* dis_u1_entry_quirk; void* dis_enblslpm_quirk; void* dis_u2_susphy_quirk; void* dis_u3_susphy_quirk; void* rx_detect_poll_quirk; void* lfps_filter_quirk; void* del_phy_power_chg_quirk; void* del_p1p2p3_quirk; void* req_p1p2p3_quirk; void* u2ss_inp3_quirk; void* u2exit_lfps_quirk; void* disable_scramble_quirk; void* usb2_lpm_disable; void* usb3_lpm_capable; void* dis_start_transfer_quirk; void* is_utmi_l1_suspend; void* has_lpm_erratum; struct device* dev; struct device* sysdev; void* sysdev_is_parent; int /*<<< orphan*/  hsphy_mode; int /*<<< orphan*/  dr_mode; int /*<<< orphan*/  maximum_speed; } ;
struct device {struct device* parent; int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 void* device_property_read_bool (struct device*,char*) ; 
 int /*<<< orphan*/  device_property_read_string (struct device*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_property_read_u32 (struct device*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_property_read_u8 (struct device*,char*,void**) ; 
 int /*<<< orphan*/  of_usb_get_phy_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_get_dr_mode (struct device*) ; 
 int /*<<< orphan*/  usb_get_maximum_speed (struct device*) ; 

__attribute__((used)) static void dwc3_get_properties(struct dwc3 *dwc)
{
	struct device		*dev = dwc->dev;
	u8			lpm_nyet_threshold;
	u8			tx_de_emphasis;
	u8			hird_threshold;
	u8			rx_thr_num_pkt_prd;
	u8			rx_max_burst_prd;
	u8			tx_thr_num_pkt_prd;
	u8			tx_max_burst_prd;

	/* default to highest possible threshold */
	lpm_nyet_threshold = 0xf;

	/* default to -3.5dB de-emphasis */
	tx_de_emphasis = 1;

	/*
	 * default to assert utmi_sleep_n and use maximum allowed HIRD
	 * threshold value of 0b1100
	 */
	hird_threshold = 12;

	dwc->maximum_speed = usb_get_maximum_speed(dev);
	dwc->dr_mode = usb_get_dr_mode(dev);
	dwc->hsphy_mode = of_usb_get_phy_mode(dev->of_node);

	dwc->sysdev_is_parent = device_property_read_bool(dev,
				"linux,sysdev_is_parent");
	if (dwc->sysdev_is_parent)
		dwc->sysdev = dwc->dev->parent;
	else
		dwc->sysdev = dwc->dev;

	dwc->has_lpm_erratum = device_property_read_bool(dev,
				"snps,has-lpm-erratum");
	device_property_read_u8(dev, "snps,lpm-nyet-threshold",
				&lpm_nyet_threshold);
	dwc->is_utmi_l1_suspend = device_property_read_bool(dev,
				"snps,is-utmi-l1-suspend");
	device_property_read_u8(dev, "snps,hird-threshold",
				&hird_threshold);
	dwc->dis_start_transfer_quirk = device_property_read_bool(dev,
				"snps,dis-start-transfer-quirk");
	dwc->usb3_lpm_capable = device_property_read_bool(dev,
				"snps,usb3_lpm_capable");
	dwc->usb2_lpm_disable = device_property_read_bool(dev,
				"snps,usb2-lpm-disable");
	device_property_read_u8(dev, "snps,rx-thr-num-pkt-prd",
				&rx_thr_num_pkt_prd);
	device_property_read_u8(dev, "snps,rx-max-burst-prd",
				&rx_max_burst_prd);
	device_property_read_u8(dev, "snps,tx-thr-num-pkt-prd",
				&tx_thr_num_pkt_prd);
	device_property_read_u8(dev, "snps,tx-max-burst-prd",
				&tx_max_burst_prd);

	dwc->disable_scramble_quirk = device_property_read_bool(dev,
				"snps,disable_scramble_quirk");
	dwc->u2exit_lfps_quirk = device_property_read_bool(dev,
				"snps,u2exit_lfps_quirk");
	dwc->u2ss_inp3_quirk = device_property_read_bool(dev,
				"snps,u2ss_inp3_quirk");
	dwc->req_p1p2p3_quirk = device_property_read_bool(dev,
				"snps,req_p1p2p3_quirk");
	dwc->del_p1p2p3_quirk = device_property_read_bool(dev,
				"snps,del_p1p2p3_quirk");
	dwc->del_phy_power_chg_quirk = device_property_read_bool(dev,
				"snps,del_phy_power_chg_quirk");
	dwc->lfps_filter_quirk = device_property_read_bool(dev,
				"snps,lfps_filter_quirk");
	dwc->rx_detect_poll_quirk = device_property_read_bool(dev,
				"snps,rx_detect_poll_quirk");
	dwc->dis_u3_susphy_quirk = device_property_read_bool(dev,
				"snps,dis_u3_susphy_quirk");
	dwc->dis_u2_susphy_quirk = device_property_read_bool(dev,
				"snps,dis_u2_susphy_quirk");
	dwc->dis_enblslpm_quirk = device_property_read_bool(dev,
				"snps,dis_enblslpm_quirk");
	dwc->dis_u1_entry_quirk = device_property_read_bool(dev,
				"snps,dis-u1-entry-quirk");
	dwc->dis_u2_entry_quirk = device_property_read_bool(dev,
				"snps,dis-u2-entry-quirk");
	dwc->dis_rxdet_inp3_quirk = device_property_read_bool(dev,
				"snps,dis_rxdet_inp3_quirk");
	dwc->dis_u2_freeclk_exists_quirk = device_property_read_bool(dev,
				"snps,dis-u2-freeclk-exists-quirk");
	dwc->dis_del_phy_power_chg_quirk = device_property_read_bool(dev,
				"snps,dis-del-phy-power-chg-quirk");
	dwc->dis_tx_ipgap_linecheck_quirk = device_property_read_bool(dev,
				"snps,dis-tx-ipgap-linecheck-quirk");

	dwc->tx_de_emphasis_quirk = device_property_read_bool(dev,
				"snps,tx_de_emphasis_quirk");
	device_property_read_u8(dev, "snps,tx_de_emphasis",
				&tx_de_emphasis);
	device_property_read_string(dev, "snps,hsphy_interface",
				    &dwc->hsphy_interface);
	device_property_read_u32(dev, "snps,quirk-frame-length-adjustment",
				 &dwc->fladj);

	dwc->dis_metastability_quirk = device_property_read_bool(dev,
				"snps,dis_metastability_quirk");

	dwc->lpm_nyet_threshold = lpm_nyet_threshold;
	dwc->tx_de_emphasis = tx_de_emphasis;

	dwc->hird_threshold = hird_threshold;

	dwc->rx_thr_num_pkt_prd = rx_thr_num_pkt_prd;
	dwc->rx_max_burst_prd = rx_max_burst_prd;

	dwc->tx_thr_num_pkt_prd = tx_thr_num_pkt_prd;
	dwc->tx_max_burst_prd = tx_max_burst_prd;

	dwc->imod_interval = 0;
}