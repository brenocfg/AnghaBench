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
struct iw_point {int /*<<< orphan*/  pointer; } ;
union iwreq_data {struct iw_point data; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct _adapter {int /*<<< orphan*/  pid; scalar_t__ driver_stopped; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ copy_from_user (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct _adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int r871x_set_pid(struct net_device *dev,
				struct iw_request_info *info,
				union iwreq_data *wrqu, char *extra)
{
	struct _adapter *padapter = netdev_priv(dev);
	struct iw_point *pdata = &wrqu->data;

	if ((padapter->driver_stopped) || (pdata == NULL))
		return -EINVAL;
	if (copy_from_user(&padapter->pid, pdata->pointer, sizeof(int)))
		return -EINVAL;
	return 0;
}