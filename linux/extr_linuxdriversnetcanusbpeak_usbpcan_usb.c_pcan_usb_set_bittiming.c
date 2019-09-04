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
typedef  int u8 ;
struct TYPE_2__ {int ctrlmode; } ;
struct peak_usb_device {int /*<<< orphan*/  netdev; TYPE_1__ can; } ;
struct can_bittiming {int brp; int sjw; int prop_seg; int phase_seg1; int phase_seg2; } ;

/* Variables and functions */
 int CAN_CTRLMODE_3_SAMPLES ; 
 int PCAN_USB_CMD_ARGS_LEN ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,int,int) ; 
 int pcan_usb_send_cmd (struct peak_usb_device*,int,int,int*) ; 

__attribute__((used)) static int pcan_usb_set_bittiming(struct peak_usb_device *dev,
				  struct can_bittiming *bt)
{
	u8 args[PCAN_USB_CMD_ARGS_LEN];
	u8 btr0, btr1;

	btr0 = ((bt->brp - 1) & 0x3f) | (((bt->sjw - 1) & 0x3) << 6);
	btr1 = ((bt->prop_seg + bt->phase_seg1 - 1) & 0xf) |
		(((bt->phase_seg2 - 1) & 0x7) << 4);
	if (dev->can.ctrlmode & CAN_CTRLMODE_3_SAMPLES)
		btr1 |= 0x80;

	netdev_info(dev->netdev, "setting BTR0=0x%02x BTR1=0x%02x\n",
		btr0, btr1);

	args[0] = btr1;
	args[1] = btr0;

	return pcan_usb_send_cmd(dev, 1, 2, args);
}