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
struct kaweth_device {scalar_t__ packet_filter_bitmap; int /*<<< orphan*/  net; TYPE_1__* intf; int /*<<< orphan*/  scratch; int /*<<< orphan*/  dev; } ;
typedef  scalar_t__ __u16 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  KAWETH_COMMAND_SET_PACKET_FILTER ; 
 int /*<<< orphan*/  KAWETH_CONTROL_TIMEOUT ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_DEVICE ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ in_interrupt () ; 
 int kaweth_control (struct kaweth_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kaweth_async_set_rx_mode(struct kaweth_device *kaweth)
{
	int result;
	__u16 packet_filter_bitmap = kaweth->packet_filter_bitmap;

	kaweth->packet_filter_bitmap = 0;
	if (packet_filter_bitmap == 0)
		return;

	if (in_interrupt())
		return;

	result = kaweth_control(kaweth,
				usb_sndctrlpipe(kaweth->dev, 0),
				KAWETH_COMMAND_SET_PACKET_FILTER,
				USB_TYPE_VENDOR | USB_DIR_OUT | USB_RECIP_DEVICE,
				packet_filter_bitmap,
				0,
				(void *)&kaweth->scratch,
				0,
				KAWETH_CONTROL_TIMEOUT);

	if(result < 0) {
		dev_err(&kaweth->intf->dev, "Failed to set Rx mode: %d\n",
			result);
	}
	else {
		netdev_dbg(kaweth->net, "Set Rx mode to %d\n",
			   packet_filter_bitmap);
	}
}