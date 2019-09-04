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
struct TYPE_4__ {int /*<<< orphan*/  info1; } ;
struct kvaser_cmd {TYPE_2__ error_event; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  CMD_FLUSH_QUEUE 132 
#define  CMD_SET_BUSPARAMS_FD_REQ 131 
#define  CMD_SET_BUSPARAMS_REQ 130 
#define  CMD_START_CHIP_REQ 129 
#define  CMD_STOP_CHIP_REQ 128 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,...) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kvaser_usb_hydra_error_event_parameter(const struct kvaser_usb *dev,
						   const struct kvaser_cmd *cmd)
{
	/* info1 will contain the offending cmd_no */
	switch (le16_to_cpu(cmd->error_event.info1)) {
	case CMD_START_CHIP_REQ:
		dev_warn(&dev->intf->dev,
			 "CMD_START_CHIP_REQ error in parameter\n");
		break;

	case CMD_STOP_CHIP_REQ:
		dev_warn(&dev->intf->dev,
			 "CMD_STOP_CHIP_REQ error in parameter\n");
		break;

	case CMD_FLUSH_QUEUE:
		dev_warn(&dev->intf->dev,
			 "CMD_FLUSH_QUEUE error in parameter\n");
		break;

	case CMD_SET_BUSPARAMS_REQ:
		dev_warn(&dev->intf->dev,
			 "Set bittiming failed. Error in parameter\n");
		break;

	case CMD_SET_BUSPARAMS_FD_REQ:
		dev_warn(&dev->intf->dev,
			 "Set data bittiming failed. Error in parameter\n");
		break;

	default:
		dev_warn(&dev->intf->dev,
			 "Unhandled parameter error event cmd_no (%u)\n",
			 le16_to_cpu(cmd->error_event.info1));
		break;
	}
}