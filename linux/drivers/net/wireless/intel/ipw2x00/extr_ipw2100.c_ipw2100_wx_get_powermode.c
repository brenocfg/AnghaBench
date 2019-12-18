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
struct TYPE_2__ {scalar_t__ length; } ;
union iwreq_data {TYPE_1__ data; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct ipw2100_priv {int power_mode; } ;
typedef  int s32 ;

/* Variables and functions */
#define  IPW_POWER_AUTO 129 
 int IPW_POWER_ENABLED ; 
 int IPW_POWER_LEVEL (int) ; 
#define  IPW_POWER_MODE_CAM 128 
 int /*<<< orphan*/  MAX_POWER_STRING ; 
 struct ipw2100_priv* libipw_priv (struct net_device*) ; 
 int* period_duration ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int,...) ; 
 scalar_t__ strlen (char*) ; 
 int* timeout_duration ; 

__attribute__((used)) static int ipw2100_wx_get_powermode(struct net_device *dev,
				    struct iw_request_info *info,
				    union iwreq_data *wrqu, char *extra)
{
	/*
	 * This can be called at any time.  No action lock required
	 */

	struct ipw2100_priv *priv = libipw_priv(dev);
	int level = IPW_POWER_LEVEL(priv->power_mode);
	s32 timeout, period;

	if (!(priv->power_mode & IPW_POWER_ENABLED)) {
		snprintf(extra, MAX_POWER_STRING,
			 "Power save level: %d (Off)", level);
	} else {
		switch (level) {
		case IPW_POWER_MODE_CAM:
			snprintf(extra, MAX_POWER_STRING,
				 "Power save level: %d (None)", level);
			break;
		case IPW_POWER_AUTO:
			snprintf(extra, MAX_POWER_STRING,
				 "Power save level: %d (Auto)", level);
			break;
		default:
			timeout = timeout_duration[level - 1] / 1000;
			period = period_duration[level - 1] / 1000;
			snprintf(extra, MAX_POWER_STRING,
				 "Power save level: %d "
				 "(Timeout %dms, Period %dms)",
				 level, timeout, period);
		}
	}

	wrqu->data.length = strlen(extra) + 1;

	return 0;
}