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
struct gs_tx_context {unsigned int echo_id; } ;
struct gs_can {int /*<<< orphan*/  tx_ctx_lock; struct gs_tx_context* tx_context; } ;

/* Variables and functions */
 unsigned int GS_MAX_TX_URBS ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct gs_tx_context *gs_get_tx_context(struct gs_can *dev,
					       unsigned int id)
{
	unsigned long flags;

	if (id < GS_MAX_TX_URBS) {
		spin_lock_irqsave(&dev->tx_ctx_lock, flags);
		if (dev->tx_context[id].echo_id == id) {
			spin_unlock_irqrestore(&dev->tx_ctx_lock, flags);
			return &dev->tx_context[id];
		}
		spin_unlock_irqrestore(&dev->tx_ctx_lock, flags);
	}
	return NULL;
}