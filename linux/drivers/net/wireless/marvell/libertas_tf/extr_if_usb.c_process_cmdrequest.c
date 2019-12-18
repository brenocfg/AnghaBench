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
typedef  int /*<<< orphan*/  uint8_t ;
struct sk_buff {int dummy; } ;
struct lbtf_private {int /*<<< orphan*/  driver_lock; int /*<<< orphan*/  cmd_resp_buff; } ;
struct if_usb_card {TYPE_1__* udev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int LBS_CMD_BUFFER_SIZE ; 
 int MESSAGE_HEADER_LEN ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  lbtf_cmd_response_rx (struct lbtf_private*) ; 
 int /*<<< orphan*/  lbtf_deb_usbd (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void process_cmdrequest(int recvlength, uint8_t *recvbuff,
				      struct sk_buff *skb,
				      struct if_usb_card *cardp,
				      struct lbtf_private *priv)
{
	unsigned long flags;

	if (recvlength < MESSAGE_HEADER_LEN ||
	    recvlength > LBS_CMD_BUFFER_SIZE) {
		lbtf_deb_usbd(&cardp->udev->dev,
			     "The receive buffer is invalid: %d\n", recvlength);
		kfree_skb(skb);
		return;
	}

	spin_lock_irqsave(&priv->driver_lock, flags);
	memcpy(priv->cmd_resp_buff, recvbuff + MESSAGE_HEADER_LEN,
	       recvlength - MESSAGE_HEADER_LEN);
	kfree_skb(skb);
	lbtf_cmd_response_rx(priv);
	spin_unlock_irqrestore(&priv->driver_lock, flags);
}