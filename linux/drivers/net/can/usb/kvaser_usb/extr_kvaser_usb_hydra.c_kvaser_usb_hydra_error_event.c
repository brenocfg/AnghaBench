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
struct kvaser_usb {TYPE_1__* intf; } ;
struct TYPE_4__ {int error_code; int /*<<< orphan*/  info1; } ;
struct kvaser_cmd {TYPE_2__ error_event; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  KVASER_USB_HYDRA_ERROR_EVENT_CAN 129 
#define  KVASER_USB_HYDRA_ERROR_EVENT_PARAM 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  kvaser_usb_hydra_error_event_parameter (struct kvaser_usb const*,struct kvaser_cmd const*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kvaser_usb_hydra_error_event(const struct kvaser_usb *dev,
					 const struct kvaser_cmd *cmd)
{
	switch (cmd->error_event.error_code) {
	case KVASER_USB_HYDRA_ERROR_EVENT_PARAM:
		kvaser_usb_hydra_error_event_parameter(dev, cmd);
		break;

	case KVASER_USB_HYDRA_ERROR_EVENT_CAN:
		/* Wrong channel mapping?! This should never happen!
		 * info1 will contain the offending cmd_no
		 */
		dev_err(&dev->intf->dev,
			"Received CAN error event for cmd_no (%u)\n",
			le16_to_cpu(cmd->error_event.info1));
		break;

	default:
		dev_warn(&dev->intf->dev,
			 "Unhandled error event (%d)\n",
			 cmd->error_event.error_code);
		break;
	}
}