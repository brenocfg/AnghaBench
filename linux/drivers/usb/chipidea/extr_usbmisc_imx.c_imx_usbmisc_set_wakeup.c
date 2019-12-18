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
struct imx_usbmisc_data {int /*<<< orphan*/  dev; } ;
struct imx_usbmisc {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* set_wakeup ) (struct imx_usbmisc_data*,int) ;} ;

/* Variables and functions */
 struct imx_usbmisc* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int stub1 (struct imx_usbmisc_data*,int) ; 

int imx_usbmisc_set_wakeup(struct imx_usbmisc_data *data, bool enabled)
{
	struct imx_usbmisc *usbmisc;

	if (!data)
		return 0;

	usbmisc = dev_get_drvdata(data->dev);
	if (!usbmisc->ops->set_wakeup)
		return 0;
	return usbmisc->ops->set_wakeup(data, enabled);
}