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
struct xlgmac_hw_ops {int /*<<< orphan*/  set_rss_lookup_table; int /*<<< orphan*/  set_rss_hash_key; int /*<<< orphan*/  disable_rss; int /*<<< orphan*/  enable_rss; int /*<<< orphan*/  read_mmc_stats; int /*<<< orphan*/  rx_mmc_int; int /*<<< orphan*/  tx_mmc_int; int /*<<< orphan*/  config_pblx8; int /*<<< orphan*/  get_tx_pbl_val; int /*<<< orphan*/  config_tx_pbl_val; int /*<<< orphan*/  get_rx_pbl_val; int /*<<< orphan*/  config_rx_pbl_val; int /*<<< orphan*/  config_osp_mode; int /*<<< orphan*/  config_tsf_mode; int /*<<< orphan*/  config_rsf_mode; int /*<<< orphan*/  config_tx_threshold; int /*<<< orphan*/  config_rx_threshold; int /*<<< orphan*/  riwt_to_usec; int /*<<< orphan*/  usec_to_riwt; int /*<<< orphan*/  config_tx_coalesce; int /*<<< orphan*/  config_rx_coalesce; int /*<<< orphan*/  update_vlan_hash_table; int /*<<< orphan*/  disable_rx_vlan_filtering; int /*<<< orphan*/  enable_rx_vlan_filtering; int /*<<< orphan*/  disable_rx_vlan_stripping; int /*<<< orphan*/  enable_rx_vlan_stripping; int /*<<< orphan*/  config_rx_flow_control; int /*<<< orphan*/  config_tx_flow_control; int /*<<< orphan*/  tx_start_xmit; int /*<<< orphan*/  is_context_desc; int /*<<< orphan*/  is_last_desc; int /*<<< orphan*/  rx_desc_reset; int /*<<< orphan*/  tx_desc_reset; int /*<<< orphan*/  rx_desc_init; int /*<<< orphan*/  tx_desc_init; int /*<<< orphan*/  set_xlgmii_100000_speed; int /*<<< orphan*/  set_xlgmii_50000_speed; int /*<<< orphan*/  set_xlgmii_40000_speed; int /*<<< orphan*/  set_xlgmii_25000_speed; int /*<<< orphan*/  disable_rx_csum; int /*<<< orphan*/  enable_rx_csum; int /*<<< orphan*/  config_rx_mode; int /*<<< orphan*/  set_mac_address; int /*<<< orphan*/  disable_int; int /*<<< orphan*/  enable_int; int /*<<< orphan*/  dev_read; int /*<<< orphan*/  dev_xmit; int /*<<< orphan*/  disable_rx; int /*<<< orphan*/  enable_rx; int /*<<< orphan*/  disable_tx; int /*<<< orphan*/  enable_tx; int /*<<< orphan*/  tx_complete; int /*<<< orphan*/  exit; int /*<<< orphan*/  init; } ;

/* Variables and functions */
 int /*<<< orphan*/  xlgmac_config_osp_mode ; 
 int /*<<< orphan*/  xlgmac_config_pblx8 ; 
 int /*<<< orphan*/  xlgmac_config_rsf_mode ; 
 int /*<<< orphan*/  xlgmac_config_rx_coalesce ; 
 int /*<<< orphan*/  xlgmac_config_rx_flow_control ; 
 int /*<<< orphan*/  xlgmac_config_rx_mode ; 
 int /*<<< orphan*/  xlgmac_config_rx_pbl_val ; 
 int /*<<< orphan*/  xlgmac_config_rx_threshold ; 
 int /*<<< orphan*/  xlgmac_config_tsf_mode ; 
 int /*<<< orphan*/  xlgmac_config_tx_coalesce ; 
 int /*<<< orphan*/  xlgmac_config_tx_flow_control ; 
 int /*<<< orphan*/  xlgmac_config_tx_pbl_val ; 
 int /*<<< orphan*/  xlgmac_config_tx_threshold ; 
 int /*<<< orphan*/  xlgmac_dev_read ; 
 int /*<<< orphan*/  xlgmac_dev_xmit ; 
 int /*<<< orphan*/  xlgmac_disable_int ; 
 int /*<<< orphan*/  xlgmac_disable_rss ; 
 int /*<<< orphan*/  xlgmac_disable_rx ; 
 int /*<<< orphan*/  xlgmac_disable_rx_csum ; 
 int /*<<< orphan*/  xlgmac_disable_rx_vlan_filtering ; 
 int /*<<< orphan*/  xlgmac_disable_rx_vlan_stripping ; 
 int /*<<< orphan*/  xlgmac_disable_tx ; 
 int /*<<< orphan*/  xlgmac_enable_int ; 
 int /*<<< orphan*/  xlgmac_enable_rss ; 
 int /*<<< orphan*/  xlgmac_enable_rx ; 
 int /*<<< orphan*/  xlgmac_enable_rx_csum ; 
 int /*<<< orphan*/  xlgmac_enable_rx_vlan_filtering ; 
 int /*<<< orphan*/  xlgmac_enable_rx_vlan_stripping ; 
 int /*<<< orphan*/  xlgmac_enable_tx ; 
 int /*<<< orphan*/  xlgmac_get_rx_pbl_val ; 
 int /*<<< orphan*/  xlgmac_get_tx_pbl_val ; 
 int /*<<< orphan*/  xlgmac_hw_exit ; 
 int /*<<< orphan*/  xlgmac_hw_init ; 
 int /*<<< orphan*/  xlgmac_is_context_desc ; 
 int /*<<< orphan*/  xlgmac_is_last_desc ; 
 int /*<<< orphan*/  xlgmac_read_mmc_stats ; 
 int /*<<< orphan*/  xlgmac_riwt_to_usec ; 
 int /*<<< orphan*/  xlgmac_rx_desc_init ; 
 int /*<<< orphan*/  xlgmac_rx_desc_reset ; 
 int /*<<< orphan*/  xlgmac_rx_mmc_int ; 
 int /*<<< orphan*/  xlgmac_set_mac_address ; 
 int /*<<< orphan*/  xlgmac_set_rss_hash_key ; 
 int /*<<< orphan*/  xlgmac_set_rss_lookup_table ; 
 int /*<<< orphan*/  xlgmac_set_xlgmii_100000_speed ; 
 int /*<<< orphan*/  xlgmac_set_xlgmii_25000_speed ; 
 int /*<<< orphan*/  xlgmac_set_xlgmii_40000_speed ; 
 int /*<<< orphan*/  xlgmac_set_xlgmii_50000_speed ; 
 int /*<<< orphan*/  xlgmac_tx_complete ; 
 int /*<<< orphan*/  xlgmac_tx_desc_init ; 
 int /*<<< orphan*/  xlgmac_tx_desc_reset ; 
 int /*<<< orphan*/  xlgmac_tx_mmc_int ; 
 int /*<<< orphan*/  xlgmac_tx_start_xmit ; 
 int /*<<< orphan*/  xlgmac_update_vlan_hash_table ; 
 int /*<<< orphan*/  xlgmac_usec_to_riwt ; 

void xlgmac_init_hw_ops(struct xlgmac_hw_ops *hw_ops)
{
	hw_ops->init = xlgmac_hw_init;
	hw_ops->exit = xlgmac_hw_exit;

	hw_ops->tx_complete = xlgmac_tx_complete;

	hw_ops->enable_tx = xlgmac_enable_tx;
	hw_ops->disable_tx = xlgmac_disable_tx;
	hw_ops->enable_rx = xlgmac_enable_rx;
	hw_ops->disable_rx = xlgmac_disable_rx;

	hw_ops->dev_xmit = xlgmac_dev_xmit;
	hw_ops->dev_read = xlgmac_dev_read;
	hw_ops->enable_int = xlgmac_enable_int;
	hw_ops->disable_int = xlgmac_disable_int;

	hw_ops->set_mac_address = xlgmac_set_mac_address;
	hw_ops->config_rx_mode = xlgmac_config_rx_mode;
	hw_ops->enable_rx_csum = xlgmac_enable_rx_csum;
	hw_ops->disable_rx_csum = xlgmac_disable_rx_csum;

	/* For MII speed configuration */
	hw_ops->set_xlgmii_25000_speed = xlgmac_set_xlgmii_25000_speed;
	hw_ops->set_xlgmii_40000_speed = xlgmac_set_xlgmii_40000_speed;
	hw_ops->set_xlgmii_50000_speed = xlgmac_set_xlgmii_50000_speed;
	hw_ops->set_xlgmii_100000_speed = xlgmac_set_xlgmii_100000_speed;

	/* For descriptor related operation */
	hw_ops->tx_desc_init = xlgmac_tx_desc_init;
	hw_ops->rx_desc_init = xlgmac_rx_desc_init;
	hw_ops->tx_desc_reset = xlgmac_tx_desc_reset;
	hw_ops->rx_desc_reset = xlgmac_rx_desc_reset;
	hw_ops->is_last_desc = xlgmac_is_last_desc;
	hw_ops->is_context_desc = xlgmac_is_context_desc;
	hw_ops->tx_start_xmit = xlgmac_tx_start_xmit;

	/* For Flow Control */
	hw_ops->config_tx_flow_control = xlgmac_config_tx_flow_control;
	hw_ops->config_rx_flow_control = xlgmac_config_rx_flow_control;

	/* For Vlan related config */
	hw_ops->enable_rx_vlan_stripping = xlgmac_enable_rx_vlan_stripping;
	hw_ops->disable_rx_vlan_stripping = xlgmac_disable_rx_vlan_stripping;
	hw_ops->enable_rx_vlan_filtering = xlgmac_enable_rx_vlan_filtering;
	hw_ops->disable_rx_vlan_filtering = xlgmac_disable_rx_vlan_filtering;
	hw_ops->update_vlan_hash_table = xlgmac_update_vlan_hash_table;

	/* For RX coalescing */
	hw_ops->config_rx_coalesce = xlgmac_config_rx_coalesce;
	hw_ops->config_tx_coalesce = xlgmac_config_tx_coalesce;
	hw_ops->usec_to_riwt = xlgmac_usec_to_riwt;
	hw_ops->riwt_to_usec = xlgmac_riwt_to_usec;

	/* For RX and TX threshold config */
	hw_ops->config_rx_threshold = xlgmac_config_rx_threshold;
	hw_ops->config_tx_threshold = xlgmac_config_tx_threshold;

	/* For RX and TX Store and Forward Mode config */
	hw_ops->config_rsf_mode = xlgmac_config_rsf_mode;
	hw_ops->config_tsf_mode = xlgmac_config_tsf_mode;

	/* For TX DMA Operating on Second Frame config */
	hw_ops->config_osp_mode = xlgmac_config_osp_mode;

	/* For RX and TX PBL config */
	hw_ops->config_rx_pbl_val = xlgmac_config_rx_pbl_val;
	hw_ops->get_rx_pbl_val = xlgmac_get_rx_pbl_val;
	hw_ops->config_tx_pbl_val = xlgmac_config_tx_pbl_val;
	hw_ops->get_tx_pbl_val = xlgmac_get_tx_pbl_val;
	hw_ops->config_pblx8 = xlgmac_config_pblx8;

	/* For MMC statistics support */
	hw_ops->tx_mmc_int = xlgmac_tx_mmc_int;
	hw_ops->rx_mmc_int = xlgmac_rx_mmc_int;
	hw_ops->read_mmc_stats = xlgmac_read_mmc_stats;

	/* For Receive Side Scaling */
	hw_ops->enable_rss = xlgmac_enable_rss;
	hw_ops->disable_rss = xlgmac_disable_rss;
	hw_ops->set_rss_hash_key = xlgmac_set_rss_hash_key;
	hw_ops->set_rss_lookup_table = xlgmac_set_rss_lookup_table;
}