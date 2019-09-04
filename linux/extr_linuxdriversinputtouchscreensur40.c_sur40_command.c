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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct sur40_state {int /*<<< orphan*/  usbdev; } ;

/* Variables and functions */
 int USB_DIR_IN ; 
 int USB_RECIP_DEVICE ; 
 int USB_TYPE_VENDOR ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sur40_command(struct sur40_state *dev,
			 u8 command, u16 index, void *buffer, u16 size)
{
	return usb_control_msg(dev->usbdev, usb_rcvctrlpipe(dev->usbdev, 0),
			       command,
			       USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_DIR_IN,
			       0x00, index, buffer, size, 1000);
}