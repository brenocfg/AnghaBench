#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int u16 ;
struct ucan_urb_context {int /*<<< orphan*/  dlc; } ;
struct TYPE_8__ {size_t tx_fifo; } ;
struct ucan_priv {int /*<<< orphan*/  echo_skb_lock; TYPE_5__* netdev; struct ucan_urb_context* context_array; TYPE_1__ device_info; } ;
struct TYPE_10__ {TYPE_2__* can_tx_complete_msg; } ;
struct ucan_message_in {TYPE_3__ msg; int /*<<< orphan*/  len; } ;
struct TYPE_11__ {int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_errors; } ;
struct TYPE_12__ {TYPE_4__ stats; } ;
struct TYPE_9__ {size_t echo_index; int flags; } ;

/* Variables and functions */
 size_t READ_ONCE (int /*<<< orphan*/ ) ; 
 int UCAN_IN_HDR_SIZE ; 
 int UCAN_TX_COMPLETE_SUCCESS ; 
 int /*<<< orphan*/  can_free_echo_skb (TYPE_5__*,size_t) ; 
 int /*<<< orphan*/  can_get_echo_skb (TYPE_5__*,size_t) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (TYPE_5__*,char*,...) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  ucan_release_context (struct ucan_priv*,struct ucan_urb_context*) ; 

__attribute__((used)) static void ucan_tx_complete_msg(struct ucan_priv *up,
				 struct ucan_message_in *m)
{
	unsigned long flags;
	u16 count, i;
	u8 echo_index, dlc;
	u16 len = le16_to_cpu(m->len);

	struct ucan_urb_context *context;

	if (len < UCAN_IN_HDR_SIZE || (len % 2 != 0)) {
		netdev_err(up->netdev, "invalid tx complete length\n");
		return;
	}

	count = (len - UCAN_IN_HDR_SIZE) / 2;
	for (i = 0; i < count; i++) {
		/* we did not submit such echo ids */
		echo_index = m->msg.can_tx_complete_msg[i].echo_index;
		if (echo_index >= up->device_info.tx_fifo) {
			up->netdev->stats.tx_errors++;
			netdev_err(up->netdev,
				   "invalid echo_index %d received\n",
				   echo_index);
			continue;
		}

		/* gather information from the context */
		context = &up->context_array[echo_index];
		dlc = READ_ONCE(context->dlc);

		/* Release context and restart queue if necessary.
		 * Also check if the context was allocated
		 */
		if (!ucan_release_context(up, context))
			continue;

		spin_lock_irqsave(&up->echo_skb_lock, flags);
		if (m->msg.can_tx_complete_msg[i].flags &
		    UCAN_TX_COMPLETE_SUCCESS) {
			/* update statistics */
			up->netdev->stats.tx_packets++;
			up->netdev->stats.tx_bytes += dlc;
			can_get_echo_skb(up->netdev, echo_index);
		} else {
			up->netdev->stats.tx_dropped++;
			can_free_echo_skb(up->netdev, echo_index);
		}
		spin_unlock_irqrestore(&up->echo_skb_lock, flags);
	}
}