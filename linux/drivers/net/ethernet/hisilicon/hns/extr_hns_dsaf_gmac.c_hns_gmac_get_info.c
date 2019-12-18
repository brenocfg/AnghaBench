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
typedef  void* u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct mac_info {int pad_and_crc_en; int port_en; int duplex; void* tx_pause_en; void* rx_pause_en; int /*<<< orphan*/  speed; int /*<<< orphan*/  tx_pause_time; int /*<<< orphan*/  auto_neg; } ;
struct hns_gmac_port_mode_cfg {int /*<<< orphan*/  an_enable; scalar_t__ pad_enable; scalar_t__ crc_add; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  enum hns_port_mode { ____Placeholder_hns_port_mode } hns_port_mode ;
typedef  enum hns_gmac_duplex_mdoe { ____Placeholder_hns_gmac_duplex_mdoe } hns_gmac_duplex_mdoe ;

/* Variables and functions */
#define  GMAC_1000M_SGMII 130 
#define  GMAC_100M_SGMII 129 
 int /*<<< orphan*/  GMAC_10M_MII ; 
#define  GMAC_10M_SGMII 128 
 int /*<<< orphan*/  MAC_SPEED_10 ; 
 int /*<<< orphan*/  MAC_SPEED_100 ; 
 int /*<<< orphan*/  MAC_SPEED_1000 ; 
 int /*<<< orphan*/  hns_gmac_get_duplex_type (void*,int*) ; 
 int /*<<< orphan*/  hns_gmac_get_en (void*,void**,void**) ; 
 int /*<<< orphan*/  hns_gmac_get_pausefrm_cfg (void*,void**,void**) ; 
 int /*<<< orphan*/  hns_gmac_get_port_mode (void*,int*) ; 
 int /*<<< orphan*/  hns_gmac_get_tx_auto_pause_frames (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hns_gmac_port_mode_get (void*,struct hns_gmac_port_mode_cfg*) ; 

__attribute__((used)) static void hns_gmac_get_info(void *mac_drv, struct mac_info *mac_info)
{
	enum hns_gmac_duplex_mdoe duplex;
	enum hns_port_mode speed;
	u32 rx_pause;
	u32 tx_pause;
	u32 rx;
	u32 tx;
	u16 fc_tx_timer;
	struct hns_gmac_port_mode_cfg port_mode = { GMAC_10M_MII, 0 };

	hns_gmac_port_mode_get(mac_drv, &port_mode);
	mac_info->pad_and_crc_en = port_mode.crc_add && port_mode.pad_enable;
	mac_info->auto_neg = port_mode.an_enable;

	hns_gmac_get_tx_auto_pause_frames(mac_drv, &fc_tx_timer);
	mac_info->tx_pause_time = fc_tx_timer;

	hns_gmac_get_en(mac_drv, &rx, &tx);
	mac_info->port_en = rx && tx;

	hns_gmac_get_duplex_type(mac_drv, &duplex);
	mac_info->duplex = duplex;

	hns_gmac_get_port_mode(mac_drv, &speed);
	switch (speed) {
	case GMAC_10M_SGMII:
		mac_info->speed = MAC_SPEED_10;
		break;
	case GMAC_100M_SGMII:
		mac_info->speed = MAC_SPEED_100;
		break;
	case GMAC_1000M_SGMII:
		mac_info->speed = MAC_SPEED_1000;
		break;
	default:
		mac_info->speed = 0;
		break;
	}

	hns_gmac_get_pausefrm_cfg(mac_drv, &rx_pause, &tx_pause);
	mac_info->rx_pause_en = rx_pause;
	mac_info->tx_pause_en = tx_pause;
}