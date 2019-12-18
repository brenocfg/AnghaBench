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
struct wifi_only_haldata {scalar_t__ ant_div_cfg; int /*<<< orphan*/  rfe_type; int /*<<< orphan*/  efuse_pg_antpath; int /*<<< orphan*/  efuse_pg_antnum; int /*<<< orphan*/  customer_id; } ;
struct wifi_only_cfg {struct wifi_only_haldata haldata_info; int /*<<< orphan*/  chip_interface; struct rtl_priv* adapter; } ;
struct TYPE_2__ {int interface; } ;
struct rtl_priv {TYPE_1__ rtlhal; } ;

/* Variables and functions */
 int /*<<< orphan*/  CUSTOMER_NORMAL ; 
#define  INTF_PCI 129 
#define  INTF_USB 128 
 int /*<<< orphan*/  WIFIONLY_INTF_PCI ; 
 int /*<<< orphan*/  WIFIONLY_INTF_UNKNOWN ; 
 int /*<<< orphan*/  WIFIONLY_INTF_USB ; 
 struct wifi_only_cfg* rtl_btc_wifi_only (struct rtl_priv*) ; 
 int /*<<< orphan*/  rtl_get_hwpg_ant_num (struct rtl_priv*) ; 
 int /*<<< orphan*/  rtl_get_hwpg_rfe_type (struct rtl_priv*) ; 
 int /*<<< orphan*/  rtl_get_hwpg_single_ant_path (struct rtl_priv*) ; 

bool exhalbtc_initlize_variables_wifi_only(struct rtl_priv *rtlpriv)
{
	struct wifi_only_cfg *wifionly_cfg = rtl_btc_wifi_only(rtlpriv);
	struct wifi_only_haldata *wifionly_haldata;

	if (!wifionly_cfg)
		return false;

	wifionly_cfg->adapter = rtlpriv;

	switch (rtlpriv->rtlhal.interface) {
	case INTF_PCI:
		wifionly_cfg->chip_interface = WIFIONLY_INTF_PCI;
		break;
	case INTF_USB:
		wifionly_cfg->chip_interface = WIFIONLY_INTF_USB;
		break;
	default:
		wifionly_cfg->chip_interface = WIFIONLY_INTF_UNKNOWN;
		break;
	}

	wifionly_haldata = &wifionly_cfg->haldata_info;

	wifionly_haldata->customer_id = CUSTOMER_NORMAL;
	wifionly_haldata->efuse_pg_antnum = rtl_get_hwpg_ant_num(rtlpriv);
	wifionly_haldata->efuse_pg_antpath =
					rtl_get_hwpg_single_ant_path(rtlpriv);
	wifionly_haldata->rfe_type = rtl_get_hwpg_rfe_type(rtlpriv);
	wifionly_haldata->ant_div_cfg = 0;

	return true;
}