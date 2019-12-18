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
struct iw_point {int dummy; } ;
union iwreq_data {struct iw_point data; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct _adapter {scalar_t__ driver_stopped; } ;

/* Variables and functions */
 int EINVAL ; 
 struct _adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  r8712_set_chplan_cmd (struct _adapter*,int) ; 

__attribute__((used)) static int r871x_set_chplan(struct net_device *dev,
				struct iw_request_info *info,
				union iwreq_data *wrqu, char *extra)
{
	int ret = 0;
	struct _adapter *padapter = netdev_priv(dev);
	struct iw_point *pdata = &wrqu->data;
	int ch_plan = -1;

	if ((padapter->driver_stopped) || (pdata == NULL)) {
		ret = -EINVAL;
		goto exit;
	}
	ch_plan = (int)*extra;
	r8712_set_chplan_cmd(padapter, ch_plan);

exit:

	return ret;
}