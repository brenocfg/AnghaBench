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
struct iw_point {int /*<<< orphan*/  pointer; } ;
union iwreq_data {struct iw_point data; } ;
typedef  int u32 ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* LedControlHandler ) (struct _adapter*,int /*<<< orphan*/ ) ;} ;
struct _adapter {TYPE_1__ ledpriv; scalar_t__ driver_stopped; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int /*<<< orphan*/  LED_CTL_START_WPS ; 
 int /*<<< orphan*/  LED_CTL_STOP_WPS ; 
 int /*<<< orphan*/  LED_CTL_STOP_WPS_FAIL ; 
 scalar_t__ copy_from_user (void*,int /*<<< orphan*/ ,int) ; 
 struct _adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct _adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct _adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct _adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r871x_wps_start(struct net_device *dev,
			   struct iw_request_info *info,
			   union iwreq_data *wrqu, char *extra)
{
	struct _adapter *padapter = netdev_priv(dev);
	struct iw_point *pdata = &wrqu->data;
	u32   u32wps_start = 0;

	if ((padapter->driver_stopped) || (pdata == NULL))
		return -EINVAL;
	if (copy_from_user((void *)&u32wps_start, pdata->pointer, 4))
		return -EFAULT;
	if (u32wps_start == 0)
		u32wps_start = *extra;
	if (u32wps_start == 1) /* WPS Start */
		padapter->ledpriv.LedControlHandler(padapter,
			   LED_CTL_START_WPS);
	else if (u32wps_start == 2) /* WPS Stop because of wps success */
		padapter->ledpriv.LedControlHandler(padapter,
			   LED_CTL_STOP_WPS);
	else if (u32wps_start == 3) /* WPS Stop because of wps fail */
		padapter->ledpriv.LedControlHandler(padapter,
			   LED_CTL_STOP_WPS_FAIL);
	return 0;
}