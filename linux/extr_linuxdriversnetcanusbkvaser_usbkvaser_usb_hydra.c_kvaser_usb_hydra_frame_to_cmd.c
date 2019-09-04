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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct kvaser_usb_net_priv {TYPE_2__* dev; } ;
struct TYPE_3__ {int capabilities; } ;
struct TYPE_4__ {TYPE_1__ card_data; } ;

/* Variables and functions */
 int KVASER_USB_HYDRA_CAP_EXT_CMD ; 
 void* kvaser_usb_hydra_frame_to_cmd_ext (struct kvaser_usb_net_priv const*,struct sk_buff const*,int*,int*,int /*<<< orphan*/ ) ; 
 void* kvaser_usb_hydra_frame_to_cmd_std (struct kvaser_usb_net_priv const*,struct sk_buff const*,int*,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *
kvaser_usb_hydra_frame_to_cmd(const struct kvaser_usb_net_priv *priv,
			      const struct sk_buff *skb, int *frame_len,
			      int *cmd_len, u16 transid)
{
	void *buf;

	if (priv->dev->card_data.capabilities & KVASER_USB_HYDRA_CAP_EXT_CMD)
		buf = kvaser_usb_hydra_frame_to_cmd_ext(priv, skb, frame_len,
							cmd_len, transid);
	else
		buf = kvaser_usb_hydra_frame_to_cmd_std(priv, skb, frame_len,
							cmd_len, transid);

	return buf;
}