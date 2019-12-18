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
struct usb_device {int /*<<< orphan*/  dev; } ;
struct roccat_common2_control {int value; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ROCCAT_COMMON_COMMAND_CONTROL ; 
#define  ROCCAT_COMMON_CONTROL_STATUS_BUSY 132 
#define  ROCCAT_COMMON_CONTROL_STATUS_CRITICAL 131 
#define  ROCCAT_COMMON_CONTROL_STATUS_CRITICAL_NEW 130 
#define  ROCCAT_COMMON_CONTROL_STATUS_INVALID 129 
#define  ROCCAT_COMMON_CONTROL_STATUS_OK 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int roccat_common2_receive (struct usb_device*,int /*<<< orphan*/ ,struct roccat_common2_control*,int) ; 

__attribute__((used)) static int roccat_common2_receive_control_status(struct usb_device *usb_dev)
{
	int retval;
	struct roccat_common2_control control;

	do {
		msleep(50);
		retval = roccat_common2_receive(usb_dev,
				ROCCAT_COMMON_COMMAND_CONTROL,
				&control, sizeof(struct roccat_common2_control));

		if (retval)
			return retval;

		switch (control.value) {
		case ROCCAT_COMMON_CONTROL_STATUS_OK:
			return 0;
		case ROCCAT_COMMON_CONTROL_STATUS_BUSY:
			msleep(500);
			continue;
		case ROCCAT_COMMON_CONTROL_STATUS_INVALID:
		case ROCCAT_COMMON_CONTROL_STATUS_CRITICAL:
		case ROCCAT_COMMON_CONTROL_STATUS_CRITICAL_NEW:
			return -EINVAL;
		default:
			dev_err(&usb_dev->dev,
					"roccat_common2_receive_control_status: "
					"unknown response value 0x%x\n",
					control.value);
			return -EINVAL;
		}

	} while (1);
}