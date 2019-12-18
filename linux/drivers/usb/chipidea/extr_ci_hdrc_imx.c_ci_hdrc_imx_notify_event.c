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
struct device {int dummy; } ;
struct ci_hdrc_imx_data {int /*<<< orphan*/  usbmisc_data; int /*<<< orphan*/  pinctrl_hsic_active; int /*<<< orphan*/  pinctrl; } ;
struct ci_hdrc {TYPE_1__* dev; } ;
struct TYPE_2__ {struct device* parent; } ;

/* Variables and functions */
#define  CI_HDRC_IMX_HSIC_ACTIVE_EVENT 129 
#define  CI_HDRC_IMX_HSIC_SUSPEND_EVENT 128 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct ci_hdrc_imx_data* dev_get_drvdata (struct device*) ; 
 int imx_usbmisc_hsic_set_connect (int /*<<< orphan*/ ) ; 
 int pinctrl_select_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ci_hdrc_imx_notify_event(struct ci_hdrc *ci, unsigned int event)
{
	struct device *dev = ci->dev->parent;
	struct ci_hdrc_imx_data *data = dev_get_drvdata(dev);
	int ret = 0;

	switch (event) {
	case CI_HDRC_IMX_HSIC_ACTIVE_EVENT:
		ret = pinctrl_select_state(data->pinctrl,
				data->pinctrl_hsic_active);
		if (ret)
			dev_err(dev, "hsic_active select failed, err=%d\n",
				ret);
		break;
	case CI_HDRC_IMX_HSIC_SUSPEND_EVENT:
		ret = imx_usbmisc_hsic_set_connect(data->usbmisc_data);
		if (ret)
			dev_err(dev,
				"hsic_set_connect failed, err=%d\n", ret);
		break;
	default:
		break;
	}

	return ret;
}