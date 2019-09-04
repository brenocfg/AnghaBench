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
struct mac_params {int /*<<< orphan*/  dev; int /*<<< orphan*/  vaddr; int /*<<< orphan*/  mac_mode; int /*<<< orphan*/  mac_id; } ;
struct mac_driver {int /*<<< orphan*/  update_stats; int /*<<< orphan*/  get_strings; int /*<<< orphan*/  get_regs_count; int /*<<< orphan*/  get_sset_count; int /*<<< orphan*/  get_ethtool_stats; int /*<<< orphan*/  get_regs; int /*<<< orphan*/  get_link_status; int /*<<< orphan*/  get_pause_enable; int /*<<< orphan*/  get_info; int /*<<< orphan*/ * autoneg_stat; int /*<<< orphan*/  mac_pausefrm_cfg; int /*<<< orphan*/  config_max_frame_length; int /*<<< orphan*/  set_tx_auto_pause_frames; int /*<<< orphan*/ * adjust_link; int /*<<< orphan*/  mac_free; int /*<<< orphan*/  set_rx_ignore_pause_frames; int /*<<< orphan*/ * config_half_duplex; int /*<<< orphan*/  config_pad_and_crc; int /*<<< orphan*/ * config_loopback; int /*<<< orphan*/ * set_an_mode; int /*<<< orphan*/  set_mac_addr; struct hns_mac_cb* mac_cb; int /*<<< orphan*/  dev; int /*<<< orphan*/  io_base; int /*<<< orphan*/  mac_mode; int /*<<< orphan*/  mac_id; int /*<<< orphan*/  mac_disable; int /*<<< orphan*/  mac_enable; int /*<<< orphan*/  mac_init; } ;
struct hns_mac_cb {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct mac_driver* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_xgmac_config_max_frame_length ; 
 int /*<<< orphan*/  hns_xgmac_config_pad_and_crc ; 
 int /*<<< orphan*/  hns_xgmac_disable ; 
 int /*<<< orphan*/  hns_xgmac_enable ; 
 int /*<<< orphan*/  hns_xgmac_free ; 
 int /*<<< orphan*/  hns_xgmac_get_info ; 
 int /*<<< orphan*/  hns_xgmac_get_link_status ; 
 int /*<<< orphan*/  hns_xgmac_get_pausefrm_cfg ; 
 int /*<<< orphan*/  hns_xgmac_get_regs ; 
 int /*<<< orphan*/  hns_xgmac_get_regs_count ; 
 int /*<<< orphan*/  hns_xgmac_get_sset_count ; 
 int /*<<< orphan*/  hns_xgmac_get_stats ; 
 int /*<<< orphan*/  hns_xgmac_get_strings ; 
 int /*<<< orphan*/  hns_xgmac_init ; 
 int /*<<< orphan*/  hns_xgmac_pausefrm_cfg ; 
 int /*<<< orphan*/  hns_xgmac_set_pausefrm_mac_addr ; 
 int /*<<< orphan*/  hns_xgmac_set_rx_ignore_pause_frames ; 
 int /*<<< orphan*/  hns_xgmac_set_tx_auto_pause_frames ; 
 int /*<<< orphan*/  hns_xgmac_update_stats ; 

void *hns_xgmac_config(struct hns_mac_cb *mac_cb, struct mac_params *mac_param)
{
	struct mac_driver *mac_drv;

	mac_drv = devm_kzalloc(mac_cb->dev, sizeof(*mac_drv), GFP_KERNEL);
	if (!mac_drv)
		return NULL;

	mac_drv->mac_init = hns_xgmac_init;
	mac_drv->mac_enable = hns_xgmac_enable;
	mac_drv->mac_disable = hns_xgmac_disable;

	mac_drv->mac_id = mac_param->mac_id;
	mac_drv->mac_mode = mac_param->mac_mode;
	mac_drv->io_base = mac_param->vaddr;
	mac_drv->dev = mac_param->dev;
	mac_drv->mac_cb = mac_cb;

	mac_drv->set_mac_addr = hns_xgmac_set_pausefrm_mac_addr;
	mac_drv->set_an_mode = NULL;
	mac_drv->config_loopback = NULL;
	mac_drv->config_pad_and_crc = hns_xgmac_config_pad_and_crc;
	mac_drv->config_half_duplex = NULL;
	mac_drv->set_rx_ignore_pause_frames =
		hns_xgmac_set_rx_ignore_pause_frames;
	mac_drv->mac_free = hns_xgmac_free;
	mac_drv->adjust_link = NULL;
	mac_drv->set_tx_auto_pause_frames = hns_xgmac_set_tx_auto_pause_frames;
	mac_drv->config_max_frame_length = hns_xgmac_config_max_frame_length;
	mac_drv->mac_pausefrm_cfg = hns_xgmac_pausefrm_cfg;
	mac_drv->autoneg_stat = NULL;
	mac_drv->get_info = hns_xgmac_get_info;
	mac_drv->get_pause_enable = hns_xgmac_get_pausefrm_cfg;
	mac_drv->get_link_status = hns_xgmac_get_link_status;
	mac_drv->get_regs = hns_xgmac_get_regs;
	mac_drv->get_ethtool_stats = hns_xgmac_get_stats;
	mac_drv->get_sset_count = hns_xgmac_get_sset_count;
	mac_drv->get_regs_count = hns_xgmac_get_regs_count;
	mac_drv->get_strings = hns_xgmac_get_strings;
	mac_drv->update_stats = hns_xgmac_update_stats;

	return (void *)mac_drv;
}