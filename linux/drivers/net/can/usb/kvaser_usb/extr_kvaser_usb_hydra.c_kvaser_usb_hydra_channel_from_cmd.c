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
typedef  scalar_t__ u8 ;
struct TYPE_3__ {scalar_t__* channel_to_he; } ;
struct TYPE_4__ {TYPE_1__ hydra; } ;
struct kvaser_usb {TYPE_2__ card_data; } ;
struct kvaser_cmd {int dummy; } ;

/* Variables and functions */
 int KVASER_USB_MAX_NET_DEVICES ; 
 scalar_t__ kvaser_usb_hydra_get_cmd_src_he (struct kvaser_cmd const*) ; 

__attribute__((used)) static u8 kvaser_usb_hydra_channel_from_cmd(const struct kvaser_usb *dev,
					    const struct kvaser_cmd *cmd)
{
	int i;
	u8 channel = 0xff;
	u8 src_he = kvaser_usb_hydra_get_cmd_src_he(cmd);

	for (i = 0; i < KVASER_USB_MAX_NET_DEVICES; i++) {
		if (dev->card_data.hydra.channel_to_he[i] == src_he) {
			channel = i;
			break;
		}
	}

	return channel;
}