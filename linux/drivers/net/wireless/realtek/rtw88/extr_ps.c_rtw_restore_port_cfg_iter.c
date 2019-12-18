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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct rtw_vif {int dummy; } ;
struct rtw_dev {int dummy; } ;
struct ieee80211_vif {scalar_t__ drv_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtw_vif_port_config (struct rtw_dev*,struct rtw_vif*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtw_restore_port_cfg_iter(void *data, u8 *mac,
				      struct ieee80211_vif *vif)
{
	struct rtw_dev *rtwdev = data;
	struct rtw_vif *rtwvif = (struct rtw_vif *)vif->drv_priv;
	u32 config = ~0;

	rtw_vif_port_config(rtwdev, rtwvif, config);
}