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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  IEEE_MLME_STA_DEAUTH 129 
#define  IEEE_MLME_STA_DISASSOC 128 
 scalar_t__ rtw_netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  rtw_set_802_11_disassociate (struct adapter*) ; 

__attribute__((used)) static int wpa_mlme(struct net_device *dev, u32 command, u32 reason)
{
	int ret = 0;
	struct adapter *padapter = (struct adapter *)rtw_netdev_priv(dev);

	switch (command) {
	case IEEE_MLME_STA_DEAUTH:

		if (!rtw_set_802_11_disassociate(padapter))
			ret = -1;

		break;

	case IEEE_MLME_STA_DISASSOC:

		if (!rtw_set_802_11_disassociate(padapter))
			ret = -1;

		break;

	default:
		ret = -EOPNOTSUPP;
		break;
	}

	return ret;

}