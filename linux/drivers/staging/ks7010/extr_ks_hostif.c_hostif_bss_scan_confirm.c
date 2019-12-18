#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ flags; scalar_t__ length; } ;
union iwreq_data {TYPE_1__ data; } ;
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  sme_flag; } ;
struct ks_wlan_private {int /*<<< orphan*/  scan_ind_count; TYPE_2__ sme_i; struct net_device* net_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIOCGIWSCAN ; 
 int /*<<< orphan*/  SME_AP_SCAN ; 
 int /*<<< orphan*/  SME_BSS_SCAN_CONFIRM ; 
 int /*<<< orphan*/  get_dword (struct ks_wlan_private*) ; 
 int /*<<< orphan*/  hostif_sme_enqueue (struct ks_wlan_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wireless_send_event (struct net_device*,int /*<<< orphan*/ ,union iwreq_data*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
void hostif_bss_scan_confirm(struct ks_wlan_private *priv)
{
	u32 result_code;
	struct net_device *dev = priv->net_dev;
	union iwreq_data wrqu;

	result_code = get_dword(priv);
	netdev_dbg(priv->net_dev, "result=%d :: scan_ind_count=%d\n",
		   result_code, priv->scan_ind_count);

	priv->sme_i.sme_flag &= ~SME_AP_SCAN;
	hostif_sme_enqueue(priv, SME_BSS_SCAN_CONFIRM);

	wrqu.data.length = 0;
	wrqu.data.flags = 0;
	wireless_send_event(dev, SIOCGIWSCAN, &wrqu, NULL);
	priv->scan_ind_count = 0;
}