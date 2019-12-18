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
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_point {int length; scalar_t__ flags; } ;
struct TYPE_11__ {int length; int flags; } ;
struct TYPE_9__ {int /*<<< orphan*/  level; int /*<<< orphan*/  qual; } ;
struct TYPE_8__ {scalar_t__ e; int /*<<< orphan*/  m; } ;
struct TYPE_7__ {int /*<<< orphan*/  sa_data; int /*<<< orphan*/  sa_family; } ;
struct TYPE_12__ {TYPE_5__ data; TYPE_3__ qual; TYPE_2__ freq; int /*<<< orphan*/  mode; TYPE_1__ ap_addr; } ;
struct iw_event {TYPE_6__ u; int /*<<< orphan*/  cmd; } ;
struct atmel_private {scalar_t__ site_survey_state; int BSS_list_entries; TYPE_4__* BSSinfo; } ;
struct TYPE_10__ {int SSIDsize; scalar_t__ UsingWEP; int /*<<< orphan*/  RSSI; int /*<<< orphan*/  channel; int /*<<< orphan*/  BSStype; int /*<<< orphan*/ * SSID; int /*<<< orphan*/  BSSID; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_ETHER ; 
 int EAGAIN ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  IWEVQUAL ; 
 int IW_ENCODE_DISABLED ; 
 int IW_ENCODE_ENABLED ; 
 int IW_ENCODE_NOKEY ; 
 int /*<<< orphan*/  IW_EV_ADDR_LEN ; 
 int /*<<< orphan*/  IW_EV_FREQ_LEN ; 
 int /*<<< orphan*/  IW_EV_QUAL_LEN ; 
 int /*<<< orphan*/  IW_EV_UINT_LEN ; 
 int IW_SCAN_MAX_DATA ; 
 int /*<<< orphan*/  SIOCGIWAP ; 
 int /*<<< orphan*/  SIOCGIWENCODE ; 
 int /*<<< orphan*/  SIOCGIWESSID ; 
 int /*<<< orphan*/  SIOCGIWFREQ ; 
 int /*<<< orphan*/  SIOCGIWMODE ; 
 scalar_t__ SITE_SURVEY_COMPLETED ; 
 char* iwe_stream_add_event (struct iw_request_info*,char*,char*,struct iw_event*,int /*<<< orphan*/ ) ; 
 char* iwe_stream_add_point (struct iw_request_info*,char*,char*,struct iw_event*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct atmel_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int atmel_get_scan(struct net_device *dev,
			  struct iw_request_info *info,
			  struct iw_point *dwrq,
			  char *extra)
{
	struct atmel_private *priv = netdev_priv(dev);
	int i;
	char *current_ev = extra;
	struct iw_event	iwe;

	if (priv->site_survey_state != SITE_SURVEY_COMPLETED)
		return -EAGAIN;

	for (i = 0; i < priv->BSS_list_entries; i++) {
		iwe.cmd = SIOCGIWAP;
		iwe.u.ap_addr.sa_family = ARPHRD_ETHER;
		memcpy(iwe.u.ap_addr.sa_data, priv->BSSinfo[i].BSSID, ETH_ALEN);
		current_ev = iwe_stream_add_event(info, current_ev,
						  extra + IW_SCAN_MAX_DATA,
						  &iwe, IW_EV_ADDR_LEN);

		iwe.u.data.length =  priv->BSSinfo[i].SSIDsize;
		if (iwe.u.data.length > 32)
			iwe.u.data.length = 32;
		iwe.cmd = SIOCGIWESSID;
		iwe.u.data.flags = 1;
		current_ev = iwe_stream_add_point(info, current_ev,
						  extra + IW_SCAN_MAX_DATA,
						  &iwe, priv->BSSinfo[i].SSID);

		iwe.cmd = SIOCGIWMODE;
		iwe.u.mode = priv->BSSinfo[i].BSStype;
		current_ev = iwe_stream_add_event(info, current_ev,
						  extra + IW_SCAN_MAX_DATA,
						  &iwe, IW_EV_UINT_LEN);

		iwe.cmd = SIOCGIWFREQ;
		iwe.u.freq.m = priv->BSSinfo[i].channel;
		iwe.u.freq.e = 0;
		current_ev = iwe_stream_add_event(info, current_ev,
						  extra + IW_SCAN_MAX_DATA,
						  &iwe, IW_EV_FREQ_LEN);

		/* Add quality statistics */
		iwe.cmd = IWEVQUAL;
		iwe.u.qual.level = priv->BSSinfo[i].RSSI;
		iwe.u.qual.qual  = iwe.u.qual.level;
		/* iwe.u.qual.noise  = SOMETHING */
		current_ev = iwe_stream_add_event(info, current_ev,
						  extra + IW_SCAN_MAX_DATA,
						  &iwe, IW_EV_QUAL_LEN);


		iwe.cmd = SIOCGIWENCODE;
		if (priv->BSSinfo[i].UsingWEP)
			iwe.u.data.flags = IW_ENCODE_ENABLED | IW_ENCODE_NOKEY;
		else
			iwe.u.data.flags = IW_ENCODE_DISABLED;
		iwe.u.data.length = 0;
		current_ev = iwe_stream_add_point(info, current_ev,
						  extra + IW_SCAN_MAX_DATA,
						  &iwe, NULL);
	}

	/* Length of data */
	dwrq->length = (current_ev - extra);
	dwrq->flags = 0;

	return 0;
}