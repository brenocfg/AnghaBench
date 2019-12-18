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
struct xgbe_hw_if {int /*<<< orphan*/  set_vxlan_id; int /*<<< orphan*/  disable_vxlan; int /*<<< orphan*/  enable_vxlan; int /*<<< orphan*/  disable_ecc_sec; int /*<<< orphan*/  disable_ecc_ded; int /*<<< orphan*/  set_rss_lookup_table; int /*<<< orphan*/  set_rss_hash_key; int /*<<< orphan*/  disable_rss; int /*<<< orphan*/  enable_rss; int /*<<< orphan*/  config_dcb_pfc; int /*<<< orphan*/  config_dcb_tc; int /*<<< orphan*/  config_tc; int /*<<< orphan*/  get_tx_tstamp; int /*<<< orphan*/  get_tstamp_time; int /*<<< orphan*/  set_tstamp_time; int /*<<< orphan*/  update_tstamp_addend; int /*<<< orphan*/  config_tstamp; int /*<<< orphan*/  read_mmc_stats; int /*<<< orphan*/  rx_mmc_int; int /*<<< orphan*/  tx_mmc_int; int /*<<< orphan*/  config_osp_mode; int /*<<< orphan*/  config_tsf_mode; int /*<<< orphan*/  config_rsf_mode; int /*<<< orphan*/  config_tx_threshold; int /*<<< orphan*/  config_rx_threshold; int /*<<< orphan*/  riwt_to_usec; int /*<<< orphan*/  usec_to_riwt; int /*<<< orphan*/  config_tx_coalesce; int /*<<< orphan*/  config_rx_coalesce; int /*<<< orphan*/  config_rx_flow_control; int /*<<< orphan*/  config_tx_flow_control; int /*<<< orphan*/  tx_start_xmit; int /*<<< orphan*/  is_context_desc; int /*<<< orphan*/  is_last_desc; int /*<<< orphan*/  rx_desc_reset; int /*<<< orphan*/  tx_desc_reset; int /*<<< orphan*/  rx_desc_init; int /*<<< orphan*/  tx_desc_init; int /*<<< orphan*/  exit; int /*<<< orphan*/  init; int /*<<< orphan*/  disable_int; int /*<<< orphan*/  enable_int; int /*<<< orphan*/  dev_read; int /*<<< orphan*/  dev_xmit; int /*<<< orphan*/  powerdown_rx; int /*<<< orphan*/  powerup_rx; int /*<<< orphan*/  powerdown_tx; int /*<<< orphan*/  powerup_tx; int /*<<< orphan*/  disable_rx; int /*<<< orphan*/  enable_rx; int /*<<< orphan*/  disable_tx; int /*<<< orphan*/  enable_tx; int /*<<< orphan*/  clr_gpio; int /*<<< orphan*/  set_gpio; int /*<<< orphan*/  write_ext_mii_regs; int /*<<< orphan*/  read_ext_mii_regs; int /*<<< orphan*/  set_ext_mii_mode; int /*<<< orphan*/  set_speed; int /*<<< orphan*/  write_mmd_regs; int /*<<< orphan*/  read_mmd_regs; int /*<<< orphan*/  update_vlan_hash_table; int /*<<< orphan*/  disable_rx_vlan_filtering; int /*<<< orphan*/  enable_rx_vlan_filtering; int /*<<< orphan*/  disable_rx_vlan_stripping; int /*<<< orphan*/  enable_rx_vlan_stripping; int /*<<< orphan*/  disable_rx_csum; int /*<<< orphan*/  enable_rx_csum; int /*<<< orphan*/  config_rx_mode; int /*<<< orphan*/  set_mac_address; int /*<<< orphan*/  tx_complete; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGPR (char*) ; 
 int /*<<< orphan*/  xgbe_clr_gpio ; 
 int /*<<< orphan*/  xgbe_config_dcb_pfc ; 
 int /*<<< orphan*/  xgbe_config_dcb_tc ; 
 int /*<<< orphan*/  xgbe_config_osp_mode ; 
 int /*<<< orphan*/  xgbe_config_rsf_mode ; 
 int /*<<< orphan*/  xgbe_config_rx_coalesce ; 
 int /*<<< orphan*/  xgbe_config_rx_flow_control ; 
 int /*<<< orphan*/  xgbe_config_rx_mode ; 
 int /*<<< orphan*/  xgbe_config_rx_threshold ; 
 int /*<<< orphan*/  xgbe_config_tc ; 
 int /*<<< orphan*/  xgbe_config_tsf_mode ; 
 int /*<<< orphan*/  xgbe_config_tstamp ; 
 int /*<<< orphan*/  xgbe_config_tx_coalesce ; 
 int /*<<< orphan*/  xgbe_config_tx_flow_control ; 
 int /*<<< orphan*/  xgbe_config_tx_threshold ; 
 int /*<<< orphan*/  xgbe_dev_read ; 
 int /*<<< orphan*/  xgbe_dev_xmit ; 
 int /*<<< orphan*/  xgbe_disable_ecc_ded ; 
 int /*<<< orphan*/  xgbe_disable_ecc_sec ; 
 int /*<<< orphan*/  xgbe_disable_int ; 
 int /*<<< orphan*/  xgbe_disable_rss ; 
 int /*<<< orphan*/  xgbe_disable_rx ; 
 int /*<<< orphan*/  xgbe_disable_rx_csum ; 
 int /*<<< orphan*/  xgbe_disable_rx_vlan_filtering ; 
 int /*<<< orphan*/  xgbe_disable_rx_vlan_stripping ; 
 int /*<<< orphan*/  xgbe_disable_tx ; 
 int /*<<< orphan*/  xgbe_disable_vxlan ; 
 int /*<<< orphan*/  xgbe_enable_int ; 
 int /*<<< orphan*/  xgbe_enable_rss ; 
 int /*<<< orphan*/  xgbe_enable_rx ; 
 int /*<<< orphan*/  xgbe_enable_rx_csum ; 
 int /*<<< orphan*/  xgbe_enable_rx_vlan_filtering ; 
 int /*<<< orphan*/  xgbe_enable_rx_vlan_stripping ; 
 int /*<<< orphan*/  xgbe_enable_tx ; 
 int /*<<< orphan*/  xgbe_enable_vxlan ; 
 int /*<<< orphan*/  xgbe_exit ; 
 int /*<<< orphan*/  xgbe_get_tstamp_time ; 
 int /*<<< orphan*/  xgbe_get_tx_tstamp ; 
 int /*<<< orphan*/  xgbe_init ; 
 int /*<<< orphan*/  xgbe_is_context_desc ; 
 int /*<<< orphan*/  xgbe_is_last_desc ; 
 int /*<<< orphan*/  xgbe_powerdown_rx ; 
 int /*<<< orphan*/  xgbe_powerdown_tx ; 
 int /*<<< orphan*/  xgbe_powerup_rx ; 
 int /*<<< orphan*/  xgbe_powerup_tx ; 
 int /*<<< orphan*/  xgbe_read_ext_mii_regs ; 
 int /*<<< orphan*/  xgbe_read_mmc_stats ; 
 int /*<<< orphan*/  xgbe_read_mmd_regs ; 
 int /*<<< orphan*/  xgbe_riwt_to_usec ; 
 int /*<<< orphan*/  xgbe_rx_desc_init ; 
 int /*<<< orphan*/  xgbe_rx_desc_reset ; 
 int /*<<< orphan*/  xgbe_rx_mmc_int ; 
 int /*<<< orphan*/  xgbe_set_ext_mii_mode ; 
 int /*<<< orphan*/  xgbe_set_gpio ; 
 int /*<<< orphan*/  xgbe_set_mac_address ; 
 int /*<<< orphan*/  xgbe_set_rss_hash_key ; 
 int /*<<< orphan*/  xgbe_set_rss_lookup_table ; 
 int /*<<< orphan*/  xgbe_set_speed ; 
 int /*<<< orphan*/  xgbe_set_tstamp_time ; 
 int /*<<< orphan*/  xgbe_set_vxlan_id ; 
 int /*<<< orphan*/  xgbe_tx_complete ; 
 int /*<<< orphan*/  xgbe_tx_desc_init ; 
 int /*<<< orphan*/  xgbe_tx_desc_reset ; 
 int /*<<< orphan*/  xgbe_tx_mmc_int ; 
 int /*<<< orphan*/  xgbe_tx_start_xmit ; 
 int /*<<< orphan*/  xgbe_update_tstamp_addend ; 
 int /*<<< orphan*/  xgbe_update_vlan_hash_table ; 
 int /*<<< orphan*/  xgbe_usec_to_riwt ; 
 int /*<<< orphan*/  xgbe_write_ext_mii_regs ; 
 int /*<<< orphan*/  xgbe_write_mmd_regs ; 

void xgbe_init_function_ptrs_dev(struct xgbe_hw_if *hw_if)
{
	DBGPR("-->xgbe_init_function_ptrs\n");

	hw_if->tx_complete = xgbe_tx_complete;

	hw_if->set_mac_address = xgbe_set_mac_address;
	hw_if->config_rx_mode = xgbe_config_rx_mode;

	hw_if->enable_rx_csum = xgbe_enable_rx_csum;
	hw_if->disable_rx_csum = xgbe_disable_rx_csum;

	hw_if->enable_rx_vlan_stripping = xgbe_enable_rx_vlan_stripping;
	hw_if->disable_rx_vlan_stripping = xgbe_disable_rx_vlan_stripping;
	hw_if->enable_rx_vlan_filtering = xgbe_enable_rx_vlan_filtering;
	hw_if->disable_rx_vlan_filtering = xgbe_disable_rx_vlan_filtering;
	hw_if->update_vlan_hash_table = xgbe_update_vlan_hash_table;

	hw_if->read_mmd_regs = xgbe_read_mmd_regs;
	hw_if->write_mmd_regs = xgbe_write_mmd_regs;

	hw_if->set_speed = xgbe_set_speed;

	hw_if->set_ext_mii_mode = xgbe_set_ext_mii_mode;
	hw_if->read_ext_mii_regs = xgbe_read_ext_mii_regs;
	hw_if->write_ext_mii_regs = xgbe_write_ext_mii_regs;

	hw_if->set_gpio = xgbe_set_gpio;
	hw_if->clr_gpio = xgbe_clr_gpio;

	hw_if->enable_tx = xgbe_enable_tx;
	hw_if->disable_tx = xgbe_disable_tx;
	hw_if->enable_rx = xgbe_enable_rx;
	hw_if->disable_rx = xgbe_disable_rx;

	hw_if->powerup_tx = xgbe_powerup_tx;
	hw_if->powerdown_tx = xgbe_powerdown_tx;
	hw_if->powerup_rx = xgbe_powerup_rx;
	hw_if->powerdown_rx = xgbe_powerdown_rx;

	hw_if->dev_xmit = xgbe_dev_xmit;
	hw_if->dev_read = xgbe_dev_read;
	hw_if->enable_int = xgbe_enable_int;
	hw_if->disable_int = xgbe_disable_int;
	hw_if->init = xgbe_init;
	hw_if->exit = xgbe_exit;

	/* Descriptor related Sequences have to be initialized here */
	hw_if->tx_desc_init = xgbe_tx_desc_init;
	hw_if->rx_desc_init = xgbe_rx_desc_init;
	hw_if->tx_desc_reset = xgbe_tx_desc_reset;
	hw_if->rx_desc_reset = xgbe_rx_desc_reset;
	hw_if->is_last_desc = xgbe_is_last_desc;
	hw_if->is_context_desc = xgbe_is_context_desc;
	hw_if->tx_start_xmit = xgbe_tx_start_xmit;

	/* For FLOW ctrl */
	hw_if->config_tx_flow_control = xgbe_config_tx_flow_control;
	hw_if->config_rx_flow_control = xgbe_config_rx_flow_control;

	/* For RX coalescing */
	hw_if->config_rx_coalesce = xgbe_config_rx_coalesce;
	hw_if->config_tx_coalesce = xgbe_config_tx_coalesce;
	hw_if->usec_to_riwt = xgbe_usec_to_riwt;
	hw_if->riwt_to_usec = xgbe_riwt_to_usec;

	/* For RX and TX threshold config */
	hw_if->config_rx_threshold = xgbe_config_rx_threshold;
	hw_if->config_tx_threshold = xgbe_config_tx_threshold;

	/* For RX and TX Store and Forward Mode config */
	hw_if->config_rsf_mode = xgbe_config_rsf_mode;
	hw_if->config_tsf_mode = xgbe_config_tsf_mode;

	/* For TX DMA Operating on Second Frame config */
	hw_if->config_osp_mode = xgbe_config_osp_mode;

	/* For MMC statistics support */
	hw_if->tx_mmc_int = xgbe_tx_mmc_int;
	hw_if->rx_mmc_int = xgbe_rx_mmc_int;
	hw_if->read_mmc_stats = xgbe_read_mmc_stats;

	/* For PTP config */
	hw_if->config_tstamp = xgbe_config_tstamp;
	hw_if->update_tstamp_addend = xgbe_update_tstamp_addend;
	hw_if->set_tstamp_time = xgbe_set_tstamp_time;
	hw_if->get_tstamp_time = xgbe_get_tstamp_time;
	hw_if->get_tx_tstamp = xgbe_get_tx_tstamp;

	/* For Data Center Bridging config */
	hw_if->config_tc = xgbe_config_tc;
	hw_if->config_dcb_tc = xgbe_config_dcb_tc;
	hw_if->config_dcb_pfc = xgbe_config_dcb_pfc;

	/* For Receive Side Scaling */
	hw_if->enable_rss = xgbe_enable_rss;
	hw_if->disable_rss = xgbe_disable_rss;
	hw_if->set_rss_hash_key = xgbe_set_rss_hash_key;
	hw_if->set_rss_lookup_table = xgbe_set_rss_lookup_table;

	/* For ECC */
	hw_if->disable_ecc_ded = xgbe_disable_ecc_ded;
	hw_if->disable_ecc_sec = xgbe_disable_ecc_sec;

	/* For VXLAN */
	hw_if->enable_vxlan = xgbe_enable_vxlan;
	hw_if->disable_vxlan = xgbe_disable_vxlan;
	hw_if->set_vxlan_id = xgbe_set_vxlan_id;

	DBGPR("<--xgbe_init_function_ptrs\n");
}