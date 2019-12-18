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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct cw1200_txpriv {int dummy; } ;
struct cw1200_queue_stats {int /*<<< orphan*/  priv; int /*<<< orphan*/  (* skb_dtor ) (int /*<<< orphan*/ ,struct sk_buff*,struct cw1200_txpriv*) ;} ;
struct cw1200_queue_item {size_t generation; int /*<<< orphan*/  head; struct sk_buff* skb; struct cw1200_txpriv txpriv; } ;
struct cw1200_queue {size_t queue_id; size_t generation; int capacity; int num_queued; int overfull; int /*<<< orphan*/  lock; int /*<<< orphan*/  free_pool; int /*<<< orphan*/  num_sent; int /*<<< orphan*/  num_pending; struct cw1200_queue_item* pool; struct cw1200_queue_stats* stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __cw1200_queue_unlock (struct cw1200_queue*) ; 
 int /*<<< orphan*/  cw1200_queue_parse_id (int /*<<< orphan*/ ,size_t*,size_t*,size_t*,size_t*) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct sk_buff*,struct cw1200_txpriv*) ; 

int cw1200_queue_remove(struct cw1200_queue *queue, u32 packet_id)
{
	int ret = 0;
	u8 queue_generation, queue_id, item_generation, item_id;
	struct cw1200_queue_item *item;
	struct cw1200_queue_stats *stats = queue->stats;
	struct sk_buff *gc_skb = NULL;
	struct cw1200_txpriv gc_txpriv;

	cw1200_queue_parse_id(packet_id, &queue_generation, &queue_id,
			      &item_generation, &item_id);

	item = &queue->pool[item_id];

	spin_lock_bh(&queue->lock);
	BUG_ON(queue_id != queue->queue_id);
	if (queue_generation != queue->generation) {
		ret = -ENOENT;
	} else if (item_id >= (unsigned) queue->capacity) {
		WARN_ON(1);
		ret = -EINVAL;
	} else if (item->generation != item_generation) {
		WARN_ON(1);
		ret = -ENOENT;
	} else {
		gc_txpriv = item->txpriv;
		gc_skb = item->skb;
		item->skb = NULL;
		--queue->num_pending;
		--queue->num_queued;
		++queue->num_sent;
		++item->generation;
		/* Do not use list_move_tail here, but list_move:
		 * try to utilize cache row.
		 */
		list_move(&item->head, &queue->free_pool);

		if (queue->overfull &&
		    (queue->num_queued <= (queue->capacity >> 1))) {
			queue->overfull = false;
			__cw1200_queue_unlock(queue);
		}
	}
	spin_unlock_bh(&queue->lock);

	if (gc_skb)
		stats->skb_dtor(stats->priv, gc_skb, &gc_txpriv);

	return ret;
}