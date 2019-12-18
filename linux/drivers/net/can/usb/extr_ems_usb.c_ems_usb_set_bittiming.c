#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct net_device {int dummy; } ;
struct TYPE_8__ {int btr0; int btr1; } ;
struct TYPE_9__ {TYPE_2__ sja1000; } ;
struct TYPE_10__ {TYPE_3__ cc_params; } ;
struct TYPE_11__ {TYPE_4__ can_params; } ;
struct TYPE_12__ {TYPE_5__ msg; } ;
struct can_bittiming {int brp; int sjw; int prop_seg; int phase_seg1; int phase_seg2; } ;
struct TYPE_7__ {int ctrlmode; struct can_bittiming bittiming; } ;
struct ems_usb {TYPE_6__ active_params; TYPE_1__ can; } ;

/* Variables and functions */
 int CAN_CTRLMODE_3_SAMPLES ; 
 int ems_usb_command_msg (struct ems_usb*,TYPE_6__*) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int,int) ; 
 struct ems_usb* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ems_usb_set_bittiming(struct net_device *netdev)
{
	struct ems_usb *dev = netdev_priv(netdev);
	struct can_bittiming *bt = &dev->can.bittiming;
	u8 btr0, btr1;

	btr0 = ((bt->brp - 1) & 0x3f) | (((bt->sjw - 1) & 0x3) << 6);
	btr1 = ((bt->prop_seg + bt->phase_seg1 - 1) & 0xf) |
		(((bt->phase_seg2 - 1) & 0x7) << 4);
	if (dev->can.ctrlmode & CAN_CTRLMODE_3_SAMPLES)
		btr1 |= 0x80;

	netdev_info(netdev, "setting BTR0=0x%02x BTR1=0x%02x\n", btr0, btr1);

	dev->active_params.msg.can_params.cc_params.sja1000.btr0 = btr0;
	dev->active_params.msg.can_params.cc_params.sja1000.btr1 = btr1;

	return ems_usb_command_msg(dev, &dev->active_params);
}