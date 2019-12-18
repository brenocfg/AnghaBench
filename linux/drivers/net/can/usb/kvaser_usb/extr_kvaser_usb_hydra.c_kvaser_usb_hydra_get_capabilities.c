#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct TYPE_4__ {int capabilities; } ;
struct kvaser_usb {TYPE_1__* intf; TYPE_2__ card_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int KVASER_USB_CAP_EXT_CAP ; 
 int /*<<< orphan*/  KVASER_USB_HYDRA_CAP_CMD_ERR_REPORT ; 
 int /*<<< orphan*/  KVASER_USB_HYDRA_CAP_CMD_LISTEN_MODE ; 
 int /*<<< orphan*/  KVASER_USB_HYDRA_CAP_CMD_ONE_SHOT ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int kvaser_usb_hydra_get_single_capability (struct kvaser_usb*,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static int kvaser_usb_hydra_get_capabilities(struct kvaser_usb *dev)
{
	int err;
	u16 status;

	if (!(dev->card_data.capabilities & KVASER_USB_CAP_EXT_CAP)) {
		dev_info(&dev->intf->dev,
			 "No extended capability support. Upgrade your device.\n");
		return 0;
	}

	err = kvaser_usb_hydra_get_single_capability
					(dev,
					 KVASER_USB_HYDRA_CAP_CMD_LISTEN_MODE,
					 &status);
	if (err)
		return err;
	if (status)
		dev_info(&dev->intf->dev,
			 "KVASER_USB_HYDRA_CAP_CMD_LISTEN_MODE failed %u\n",
			 status);

	err = kvaser_usb_hydra_get_single_capability
					(dev,
					 KVASER_USB_HYDRA_CAP_CMD_ERR_REPORT,
					 &status);
	if (err)
		return err;
	if (status)
		dev_info(&dev->intf->dev,
			 "KVASER_USB_HYDRA_CAP_CMD_ERR_REPORT failed %u\n",
			 status);

	err = kvaser_usb_hydra_get_single_capability
					(dev, KVASER_USB_HYDRA_CAP_CMD_ONE_SHOT,
					 &status);
	if (err)
		return err;
	if (status)
		dev_info(&dev->intf->dev,
			 "KVASER_USB_HYDRA_CAP_CMD_ONE_SHOT failed %u\n",
			 status);

	return 0;
}