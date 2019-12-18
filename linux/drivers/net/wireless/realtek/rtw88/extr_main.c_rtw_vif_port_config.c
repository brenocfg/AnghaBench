#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct rtw_vif {int /*<<< orphan*/  bcn_ctrl; TYPE_6__* conf; int /*<<< orphan*/  aid; int /*<<< orphan*/  net_type; int /*<<< orphan*/  bssid; int /*<<< orphan*/  mac_addr; } ;
struct rtw_dev {int dummy; } ;
struct TYPE_11__ {int addr; int mask; } ;
struct TYPE_10__ {int addr; int mask; } ;
struct TYPE_9__ {int addr; int mask; } ;
struct TYPE_8__ {int addr; } ;
struct TYPE_7__ {int addr; } ;
struct TYPE_12__ {TYPE_5__ bcn_ctrl; TYPE_4__ aid; TYPE_3__ net_type; TYPE_2__ bssid; TYPE_1__ mac_addr; } ;

/* Variables and functions */
 int PORT_SET_AID ; 
 int PORT_SET_BCN_CTRL ; 
 int PORT_SET_BSSID ; 
 int PORT_SET_MAC_ADDR ; 
 int PORT_SET_NET_TYPE ; 
 int /*<<< orphan*/  rtw_vif_write_addr (struct rtw_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write32_mask (struct rtw_dev*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write8_mask (struct rtw_dev*,int,int,int /*<<< orphan*/ ) ; 

void rtw_vif_port_config(struct rtw_dev *rtwdev,
			 struct rtw_vif *rtwvif,
			 u32 config)
{
	u32 addr, mask;

	if (config & PORT_SET_MAC_ADDR) {
		addr = rtwvif->conf->mac_addr.addr;
		rtw_vif_write_addr(rtwdev, addr, rtwvif->mac_addr);
	}
	if (config & PORT_SET_BSSID) {
		addr = rtwvif->conf->bssid.addr;
		rtw_vif_write_addr(rtwdev, addr, rtwvif->bssid);
	}
	if (config & PORT_SET_NET_TYPE) {
		addr = rtwvif->conf->net_type.addr;
		mask = rtwvif->conf->net_type.mask;
		rtw_write32_mask(rtwdev, addr, mask, rtwvif->net_type);
	}
	if (config & PORT_SET_AID) {
		addr = rtwvif->conf->aid.addr;
		mask = rtwvif->conf->aid.mask;
		rtw_write32_mask(rtwdev, addr, mask, rtwvif->aid);
	}
	if (config & PORT_SET_BCN_CTRL) {
		addr = rtwvif->conf->bcn_ctrl.addr;
		mask = rtwvif->conf->bcn_ctrl.mask;
		rtw_write8_mask(rtwdev, addr, mask, rtwvif->bcn_ctrl);
	}
}