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
struct TYPE_2__ {int flags; scalar_t__ disabled; int /*<<< orphan*/  value; } ;
union iwreq_data {TYPE_1__ retry; } ;
typedef  int /*<<< orphan*/  u8 ;
struct wl3501_card {int dummy; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
typedef  int /*<<< orphan*/  retry ;

/* Variables and functions */
 int IW_RETRY_LIMIT ; 
 int IW_RETRY_LONG ; 
 int IW_RETRY_SHORT ; 
 int /*<<< orphan*/  WL3501_MIB_ATTR_LONG_RETRY_LIMIT ; 
 int /*<<< orphan*/  WL3501_MIB_ATTR_SHORT_RETRY_LIMIT ; 
 struct wl3501_card* netdev_priv (struct net_device*) ; 
 int wl3501_get_mib_value (struct wl3501_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int wl3501_get_retry(struct net_device *dev,
			    struct iw_request_info *info,
			    union iwreq_data *wrqu, char *extra)
{
	u8 retry; /* size checked: it is u8 */
	struct wl3501_card *this = netdev_priv(dev);
	int rc = wl3501_get_mib_value(this,
				      WL3501_MIB_ATTR_LONG_RETRY_LIMIT,
				      &retry, sizeof(retry));
	if (rc)
		goto out;
	if (wrqu->retry.flags & IW_RETRY_LONG) {
		wrqu->retry.flags = IW_RETRY_LIMIT | IW_RETRY_LONG;
		goto set_value;
	}
	rc = wl3501_get_mib_value(this, WL3501_MIB_ATTR_SHORT_RETRY_LIMIT,
				  &retry, sizeof(retry));
	if (rc)
		goto out;
	wrqu->retry.flags = IW_RETRY_LIMIT | IW_RETRY_SHORT;
set_value:
	wrqu->retry.value = retry;
	wrqu->retry.disabled = 0;
out:
	return rc;
}