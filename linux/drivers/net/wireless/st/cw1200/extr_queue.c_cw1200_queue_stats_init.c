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
struct cw1200_queue_stats {size_t map_capacity; int /*<<< orphan*/  link_map_cache; int /*<<< orphan*/  wait_link_id_empty; int /*<<< orphan*/  lock; struct cw1200_common* priv; int /*<<< orphan*/  skb_dtor; } ;
struct cw1200_common {int dummy; } ;
typedef  int /*<<< orphan*/  cw1200_queue_skb_dtor_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kcalloc (size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct cw1200_queue_stats*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int cw1200_queue_stats_init(struct cw1200_queue_stats *stats,
			    size_t map_capacity,
			    cw1200_queue_skb_dtor_t skb_dtor,
			    struct cw1200_common *priv)
{
	memset(stats, 0, sizeof(*stats));
	stats->map_capacity = map_capacity;
	stats->skb_dtor = skb_dtor;
	stats->priv = priv;
	spin_lock_init(&stats->lock);
	init_waitqueue_head(&stats->wait_link_id_empty);

	stats->link_map_cache = kcalloc(map_capacity, sizeof(int),
					GFP_KERNEL);
	if (!stats->link_map_cache)
		return -ENOMEM;

	return 0;
}