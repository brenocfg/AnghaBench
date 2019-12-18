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
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u16 ;
struct xenvif_queue {size_t* pending_ring; int /*<<< orphan*/  response_lock; int /*<<< orphan*/  pending_prod; struct pending_tx_info* pending_tx_info; } ;
struct pending_tx_info {int /*<<< orphan*/  extra_count; int /*<<< orphan*/  req; } ;
typedef  size_t pending_ring_idx_t ;

/* Variables and functions */
 int /*<<< orphan*/  make_tx_response (struct xenvif_queue*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t pending_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_tx_responses (struct xenvif_queue*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void xenvif_idx_release(struct xenvif_queue *queue, u16 pending_idx,
			       u8 status)
{
	struct pending_tx_info *pending_tx_info;
	pending_ring_idx_t index;
	unsigned long flags;

	pending_tx_info = &queue->pending_tx_info[pending_idx];

	spin_lock_irqsave(&queue->response_lock, flags);

	make_tx_response(queue, &pending_tx_info->req,
			 pending_tx_info->extra_count, status);

	/* Release the pending index before pusing the Tx response so
	 * its available before a new Tx request is pushed by the
	 * frontend.
	 */
	index = pending_index(queue->pending_prod++);
	queue->pending_ring[index] = pending_idx;

	push_tx_responses(queue);

	spin_unlock_irqrestore(&queue->response_lock, flags);
}