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
struct iw_freq {int e; int m; } ;
union iwreq_data {struct iw_freq freq; } ;
struct TYPE_2__ {size_t channel; } ;
struct rtllib_device {scalar_t__ iw_mode; int* active_channel_map; scalar_t__ state; int /*<<< orphan*/  wx_mutex; TYPE_1__ current_network; int /*<<< orphan*/  dev; int /*<<< orphan*/  (* set_chan ) (int /*<<< orphan*/ ,size_t) ;} ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 scalar_t__ IW_MODE_ADHOC ; 
 scalar_t__ IW_MODE_INFRA ; 
 scalar_t__ IW_MODE_MASTER ; 
 scalar_t__ RTLLIB_LINKED ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtllib_start_send_beacons (struct rtllib_device*) ; 
 int /*<<< orphan*/  rtllib_stop_send_beacons (struct rtllib_device*) ; 
 int* rtllib_wlan_frequencies ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,size_t) ; 

int rtllib_wx_set_freq(struct rtllib_device *ieee, struct iw_request_info *a,
			     union iwreq_data *wrqu, char *b)
{
	int ret;
	struct iw_freq *fwrq = &wrqu->freq;

	mutex_lock(&ieee->wx_mutex);

	if (ieee->iw_mode == IW_MODE_INFRA) {
		ret = 0;
		goto out;
	}

	/* if setting by freq convert to channel */
	if (fwrq->e == 1) {
		if ((fwrq->m >= (int) 2.412e8 &&
		     fwrq->m <= (int) 2.487e8)) {
			int f = fwrq->m / 100000;
			int c = 0;

			while ((c < 14) && (f != rtllib_wlan_frequencies[c]))
				c++;

			/* hack to fall through */
			fwrq->e = 0;
			fwrq->m = c + 1;
		}
	}

	if (fwrq->e > 0 || fwrq->m > 14 || fwrq->m < 1) {
		ret = -EOPNOTSUPP;
		goto out;

	} else { /* Set the channel */

		if (ieee->active_channel_map[fwrq->m] != 1) {
			ret = -EINVAL;
			goto out;
		}
		ieee->current_network.channel = fwrq->m;
		ieee->set_chan(ieee->dev, ieee->current_network.channel);

		if (ieee->iw_mode == IW_MODE_ADHOC ||
		    ieee->iw_mode == IW_MODE_MASTER)
			if (ieee->state == RTLLIB_LINKED) {
				rtllib_stop_send_beacons(ieee);
				rtllib_start_send_beacons(ieee);
			}
	}

	ret = 0;
out:
	mutex_unlock(&ieee->wx_mutex);
	return ret;
}