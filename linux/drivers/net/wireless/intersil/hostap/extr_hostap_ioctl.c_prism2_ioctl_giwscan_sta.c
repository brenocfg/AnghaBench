#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_point {int length; } ;
struct hostap_interface {TYPE_1__* local; } ;
struct TYPE_3__ {scalar_t__ scan_timestamp; } ;
typedef  TYPE_1__ local_info_t ;

/* Variables and functions */
 int EAGAIN ; 
 int EOPNOTSUPP ; 
 int HZ ; 
 int /*<<< orphan*/  jiffies ; 
 struct hostap_interface* netdev_priv (struct net_device*) ; 
 int prism2_translate_scan (TYPE_1__*,struct iw_request_info*,char*,int) ; 
 scalar_t__ time_before (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline int prism2_ioctl_giwscan_sta(struct net_device *dev,
					   struct iw_request_info *info,
					   struct iw_point *data, char *extra)
{
#ifdef PRISM2_NO_STATION_MODES
	return -EOPNOTSUPP;
#else /* PRISM2_NO_STATION_MODES */
	struct hostap_interface *iface;
	local_info_t *local;
	int res;

	iface = netdev_priv(dev);
	local = iface->local;

	/* Wait until the scan is finished. We can probably do better
	 * than that - Jean II */
	if (local->scan_timestamp &&
	    time_before(jiffies, local->scan_timestamp + 3 * HZ)) {
		/* Important note : we don't want to block the caller
		 * until results are ready for various reasons.
		 * First, managing wait queues is complex and racy
		 * (there may be multiple simultaneous callers).
		 * Second, we grab some rtnetlink lock before coming
		 * here (in dev_ioctl()).
		 * Third, the caller can wait on the Wireless Event
		 * - Jean II */
		return -EAGAIN;
	}
	local->scan_timestamp = 0;

	res = prism2_translate_scan(local, info, extra, data->length);

	if (res >= 0) {
		data->length = res;
		return 0;
	} else {
		data->length = 0;
		return res;
	}
#endif /* PRISM2_NO_STATION_MODES */
}