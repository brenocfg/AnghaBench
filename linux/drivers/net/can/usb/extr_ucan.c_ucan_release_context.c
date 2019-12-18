#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ucan_urb_context {int allocated; } ;
struct ucan_priv {int /*<<< orphan*/  context_lock; int /*<<< orphan*/  available_tx_urbs; int /*<<< orphan*/  netdev; int /*<<< orphan*/  context_array; } ;

/* Variables and functions */
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static bool ucan_release_context(struct ucan_priv *up,
				 struct ucan_urb_context *ctx)
{
	unsigned long flags;
	bool ret = false;

	if (WARN_ON_ONCE(!up->context_array))
		return false;

	/* execute context operation atomically */
	spin_lock_irqsave(&up->context_lock, flags);

	/* context was not allocated, maybe the device sent garbage */
	if (ctx->allocated) {
		ctx->allocated = false;

		/* check if the queue needs to be woken */
		if (!up->available_tx_urbs)
			netif_wake_queue(up->netdev);
		up->available_tx_urbs++;

		ret = true;
	}

	spin_unlock_irqrestore(&up->context_lock, flags);
	return ret;
}