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
struct cdns3 {int dr_mode; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
#define  USB_DR_MODE_HOST 130 
#define  USB_DR_MODE_OTG 129 
#define  USB_DR_MODE_PERIPHERAL 128 
 int cdns3_init_otg_mode (struct cdns3*) ; 
 int cdns3_set_mode (struct cdns3*,int const) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 

int cdns3_drd_update_mode(struct cdns3 *cdns)
{
	int ret = 0;

	switch (cdns->dr_mode) {
	case USB_DR_MODE_PERIPHERAL:
		ret = cdns3_set_mode(cdns, USB_DR_MODE_PERIPHERAL);
		break;
	case USB_DR_MODE_HOST:
		ret = cdns3_set_mode(cdns, USB_DR_MODE_HOST);
		break;
	case USB_DR_MODE_OTG:
		ret = cdns3_init_otg_mode(cdns);
		break;
	default:
		dev_err(cdns->dev, "Unsupported mode of operation %d\n",
			cdns->dr_mode);
		return -EINVAL;
	}

	return ret;
}