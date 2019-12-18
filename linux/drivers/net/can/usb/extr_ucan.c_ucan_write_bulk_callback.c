#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct urb {int /*<<< orphan*/  status; int /*<<< orphan*/  transfer_dma; int /*<<< orphan*/  transfer_buffer; int /*<<< orphan*/  dev; struct ucan_urb_context* context; } ;
struct ucan_urb_context {struct ucan_priv* up; } ;
struct ucan_priv {int context_array; TYPE_2__* netdev; int /*<<< orphan*/  echo_skb_lock; } ;
struct ucan_message_out {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  tx_dropped; } ;
struct TYPE_7__ {TYPE_1__ stats; } ;

/* Variables and functions */
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  can_free_echo_skb (TYPE_2__*,struct ucan_urb_context*) ; 
 int /*<<< orphan*/  netdev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  netdev_warn (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_device_present (TYPE_2__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  ucan_release_context (struct ucan_priv*,struct ucan_urb_context*) ; 
 int /*<<< orphan*/  usb_free_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ucan_write_bulk_callback(struct urb *urb)
{
	unsigned long flags;
	struct ucan_priv *up;
	struct ucan_urb_context *context = urb->context;

	/* get the urb context */
	if (WARN_ON_ONCE(!context))
		return;

	/* free up our allocated buffer */
	usb_free_coherent(urb->dev,
			  sizeof(struct ucan_message_out),
			  urb->transfer_buffer,
			  urb->transfer_dma);

	up = context->up;
	if (WARN_ON_ONCE(!up))
		return;

	/* sanity check */
	if (!netif_device_present(up->netdev))
		return;

	/* transmission failed (USB - the device will not send a TX complete) */
	if (urb->status) {
		netdev_warn(up->netdev,
			    "failed to transmit USB message to device: %d\n",
			     urb->status);

		/* update counters an cleanup */
		spin_lock_irqsave(&up->echo_skb_lock, flags);
		can_free_echo_skb(up->netdev, context - up->context_array);
		spin_unlock_irqrestore(&up->echo_skb_lock, flags);

		up->netdev->stats.tx_dropped++;

		/* release context and restart the queue if necessary */
		if (!ucan_release_context(up, context))
			netdev_err(up->netdev,
				   "urb failed, failed to release context\n");
	}
}