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
typedef  union iwreq_data {int dummy; } iwreq_data ;
typedef  int u8 ;
struct TYPE_2__ {int* bssid; char* ssid; int /*<<< orphan*/  ssid_len; } ;
struct rtllib_device {scalar_t__ state; int cannot_notify; int /*<<< orphan*/  wx_mutex; TYPE_1__ current_network; int /*<<< orphan*/  ssid_set; int /*<<< orphan*/  wap_set; int /*<<< orphan*/  dev; } ;
struct iw_request_info {int dummy; } ;
struct iw_mlme {int cmd; int /*<<< orphan*/  reason_code; } ;

/* Variables and functions */
 int ENOLINK ; 
 int EOPNOTSUPP ; 
#define  IW_MLME_DEAUTH 129 
#define  IW_MLME_DISASSOC 128 
 scalar_t__ RTLLIB_LINKED ; 
 int /*<<< orphan*/  SendDisassociation (struct rtllib_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rtllib_disassociate (struct rtllib_device*) ; 

int rtllib_wx_set_mlme(struct rtllib_device *ieee,
			       struct iw_request_info *info,
			       union iwreq_data *wrqu, char *extra)
{
	u8 i = 0;
	bool deauth = false;
	struct iw_mlme *mlme = (struct iw_mlme *) extra;

	if (ieee->state != RTLLIB_LINKED)
		return -ENOLINK;

	mutex_lock(&ieee->wx_mutex);

	switch (mlme->cmd) {
	case IW_MLME_DEAUTH:
		deauth = true;
		/* fall through */
	case IW_MLME_DISASSOC:
		if (deauth)
			netdev_info(ieee->dev, "disauth packet !\n");
		else
			netdev_info(ieee->dev, "dis associate packet!\n");

		ieee->cannot_notify = true;

		SendDisassociation(ieee, deauth, mlme->reason_code);
		rtllib_disassociate(ieee);

		ieee->wap_set = 0;
		for (i = 0; i < 6; i++)
			ieee->current_network.bssid[i] = 0x55;

		ieee->ssid_set = 0;
		ieee->current_network.ssid[0] = '\0';
		ieee->current_network.ssid_len = 0;
		break;
	default:
		mutex_unlock(&ieee->wx_mutex);
		return -EOPNOTSUPP;
	}

	mutex_unlock(&ieee->wx_mutex);

	return 0;
}