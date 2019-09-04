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
typedef  int u32 ;
struct TYPE_2__ {int ctrlmode; } ;
struct peak_usb_device {int /*<<< orphan*/  netdev; TYPE_1__ can; } ;
struct can_bittiming {int sjw; int phase_seg2; int prop_seg; int phase_seg1; int brp; } ;

/* Variables and functions */
 int CAN_CTRLMODE_3_SAMPLES ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,int) ; 
 int pcan_usb_pro_set_bitrate (struct peak_usb_device*,int) ; 

__attribute__((used)) static int pcan_usb_pro_set_bittiming(struct peak_usb_device *dev,
				      struct can_bittiming *bt)
{
	u32 ccbt;

	ccbt = (dev->can.ctrlmode & CAN_CTRLMODE_3_SAMPLES) ? 0x00800000 : 0;
	ccbt |= (bt->sjw - 1) << 24;
	ccbt |= (bt->phase_seg2 - 1) << 20;
	ccbt |= (bt->prop_seg + bt->phase_seg1 - 1) << 16; /* = tseg1 */
	ccbt |= bt->brp - 1;

	netdev_info(dev->netdev, "setting ccbt=0x%08x\n", ccbt);

	return pcan_usb_pro_set_bitrate(dev, ccbt);
}