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
struct tx_policy_cache {int /*<<< orphan*/  lock; int /*<<< orphan*/ * cache; int /*<<< orphan*/  free; } ;
struct cw1200_common {struct tx_policy_cache tx_policy_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  cw1200_tx_queues_unlock (struct cw1200_common*) ; 
 int list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int tx_policy_release (struct tx_policy_cache*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tx_policy_put(struct cw1200_common *priv, int idx)
{
	int usage, locked;
	struct tx_policy_cache *cache = &priv->tx_policy_cache;

	spin_lock_bh(&cache->lock);
	locked = list_empty(&cache->free);
	usage = tx_policy_release(cache, &cache->cache[idx]);
	if (locked && !usage) {
		/* Unlock TX queues. */
		cw1200_tx_queues_unlock(priv);
	}
	spin_unlock_bh(&cache->lock);
}