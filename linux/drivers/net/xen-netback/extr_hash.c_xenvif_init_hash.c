#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  list; int /*<<< orphan*/  lock; int /*<<< orphan*/  count; } ;
struct TYPE_4__ {TYPE_1__ cache; } ;
struct xenvif {TYPE_2__ hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 scalar_t__ xenvif_hash_cache_size ; 

void xenvif_init_hash(struct xenvif *vif)
{
	if (xenvif_hash_cache_size == 0)
		return;

	BUG_ON(vif->hash.cache.count);

	spin_lock_init(&vif->hash.cache.lock);
	INIT_LIST_HEAD(&vif->hash.cache.list);
}