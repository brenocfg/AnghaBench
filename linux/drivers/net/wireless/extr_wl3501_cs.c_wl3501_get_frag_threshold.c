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
struct TYPE_2__ {int value; int disabled; int fixed; } ;
union iwreq_data {TYPE_1__ frag; } ;
typedef  int u16 ;
typedef  int /*<<< orphan*/  threshold ;
struct wl3501_card {int dummy; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WL3501_MIB_ATTR_FRAG_THRESHOLD ; 
 struct wl3501_card* netdev_priv (struct net_device*) ; 
 int wl3501_get_mib_value (struct wl3501_card*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int wl3501_get_frag_threshold(struct net_device *dev,
				     struct iw_request_info *info,
				     union iwreq_data *wrqu, char *extra)
{
	u16 threshold; /* size checked: it is u16 */
	struct wl3501_card *this = netdev_priv(dev);
	int rc = wl3501_get_mib_value(this, WL3501_MIB_ATTR_FRAG_THRESHOLD,
				      &threshold, sizeof(threshold));
	if (!rc) {
		wrqu->frag.value = threshold;
		wrqu->frag.disabled = threshold >= 2346;
		wrqu->frag.fixed = 1;
	}
	return rc;
}