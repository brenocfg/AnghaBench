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
struct vub300_mmc_host {int /*<<< orphan*/  system_port_status; int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GET_SYSTEM_PORT_STATUS ; 
 int /*<<< orphan*/  HZ ; 
 int USB_DIR_IN ; 
 int USB_RECIP_DEVICE ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  new_system_port_status (struct vub300_mmc_host*) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void check_vub300_port_status(struct vub300_mmc_host *vub300)
{
	/*
	 * cmd_mutex is held by vub300_pollwork_thread,
	 * vub300_deadwork_thread or vub300_cmndwork_thread
	 */
	int retval;
	retval =
		usb_control_msg(vub300->udev, usb_rcvctrlpipe(vub300->udev, 0),
				GET_SYSTEM_PORT_STATUS,
				USB_DIR_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
				0x0000, 0x0000, &vub300->system_port_status,
				sizeof(vub300->system_port_status), HZ);
	if (sizeof(vub300->system_port_status) == retval)
		new_system_port_status(vub300);
}