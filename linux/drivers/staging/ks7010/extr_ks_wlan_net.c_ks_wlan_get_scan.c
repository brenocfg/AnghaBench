#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int length; scalar_t__ flags; } ;
union iwreq_data {TYPE_3__ data; } ;
struct net_device {int dummy; } ;
struct TYPE_5__ {int size; int /*<<< orphan*/ * ap; } ;
struct TYPE_4__ {int sme_flag; } ;
struct ks_wlan_private {scalar_t__ sleep_mode; TYPE_2__ aplist; TYPE_1__ sme_i; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */
 int E2BIG ; 
 int EAGAIN ; 
 int ENODATA ; 
 int EPERM ; 
 int IW_EV_ADDR_LEN ; 
 scalar_t__ SLP_SLEEP ; 
 int SME_AP_SCAN ; 
 char* ks_wlan_translate_scan (struct net_device*,struct iw_request_info*,char*,char*,int /*<<< orphan*/ *) ; 
 struct ks_wlan_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ks_wlan_get_scan(struct net_device *dev,
			    struct iw_request_info *info,
			    union iwreq_data *dwrq, char *extra)
{
	struct ks_wlan_private *priv = netdev_priv(dev);
	int i;
	char *current_ev = extra;

	if (priv->sleep_mode == SLP_SLEEP)
		return -EPERM;
	/* for SLEEP MODE */
	if (priv->sme_i.sme_flag & SME_AP_SCAN)
		return -EAGAIN;

	if (priv->aplist.size == 0) {
		/* Client error, no scan results...
		 * The caller need to restart the scan.
		 */
		return -ENODATA;
	}

	/* Read and parse all entries */
	for (i = 0; i < priv->aplist.size; i++) {
		if ((extra + dwrq->data.length) - current_ev <= IW_EV_ADDR_LEN) {
			dwrq->data.length = 0;
			return -E2BIG;
		}
		/* Translate to WE format this entry */
		current_ev = ks_wlan_translate_scan(dev, info, current_ev,
						    extra + dwrq->data.length,
						    &priv->aplist.ap[i]);
	}
	/* Length of data */
	dwrq->data.length = (current_ev - extra);
	dwrq->data.flags = 0;

	return 0;
}