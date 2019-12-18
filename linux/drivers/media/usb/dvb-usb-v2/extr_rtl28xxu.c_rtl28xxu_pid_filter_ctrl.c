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
struct rtl2832_platform_data {int (* pid_filter_ctrl ) (int /*<<< orphan*/ ,int) ;} ;
struct rtl2830_platform_data {int (* pid_filter_ctrl ) (int /*<<< orphan*/ ,int) ;} ;
struct rtl28xxu_dev {scalar_t__ chip_id; struct rtl2832_platform_data rtl2832_platform_data; struct rtl2830_platform_data rtl2830_platform_data; } ;
struct dvb_usb_adapter {int /*<<< orphan*/ * fe; } ;

/* Variables and functions */
 scalar_t__ CHIP_ID_RTL2831U ; 
 struct rtl28xxu_dev* adap_to_priv (struct dvb_usb_adapter*) ; 
 int stub1 (int /*<<< orphan*/ ,int) ; 
 int stub2 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rtl28xxu_pid_filter_ctrl(struct dvb_usb_adapter *adap, int onoff)
{
	struct rtl28xxu_dev *dev = adap_to_priv(adap);

	if (dev->chip_id == CHIP_ID_RTL2831U) {
		struct rtl2830_platform_data *pdata = &dev->rtl2830_platform_data;

		return pdata->pid_filter_ctrl(adap->fe[0], onoff);
	} else {
		struct rtl2832_platform_data *pdata = &dev->rtl2832_platform_data;

		return pdata->pid_filter_ctrl(adap->fe[0], onoff);
	}
}