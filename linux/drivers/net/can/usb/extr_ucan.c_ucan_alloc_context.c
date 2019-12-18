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
struct ucan_urb_context {int allocated; } ;
struct TYPE_2__ {int tx_fifo; } ;
struct ucan_priv {int /*<<< orphan*/  context_lock; int /*<<< orphan*/  netdev; int /*<<< orphan*/  available_tx_urbs; struct ucan_urb_context* context_array; TYPE_1__ device_info; } ;

/* Variables and functions */
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  netif_stop_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct ucan_urb_context *ucan_alloc_context(struct ucan_priv *up)
{
	int i;
	unsigned long flags;
	struct ucan_urb_context *ret = NULL;

	if (WARN_ON_ONCE(!up->context_array))
		return NULL;

	/* execute context operation atomically */
	spin_lock_irqsave(&up->context_lock, flags);

	for (i = 0; i < up->device_info.tx_fifo; i++) {
		if (!up->context_array[i].allocated) {
			/* update context */
			ret = &up->context_array[i];
			up->context_array[i].allocated = true;

			/* stop queue if necessary */
			up->available_tx_urbs--;
			if (!up->available_tx_urbs)
				netif_stop_queue(up->netdev);

			break;
		}
	}

	spin_unlock_irqrestore(&up->context_lock, flags);
	return ret;
}