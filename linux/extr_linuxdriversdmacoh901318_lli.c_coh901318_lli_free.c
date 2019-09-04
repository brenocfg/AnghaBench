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
struct coh901318_pool {int /*<<< orphan*/  lock; int /*<<< orphan*/  dmapool; } ;
struct coh901318_lli {int /*<<< orphan*/  phy_this; struct coh901318_lli* virt_link_addr; scalar_t__ link_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFS_POOL_COUNTER_ADD (struct coh901318_pool*,int) ; 
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,struct coh901318_lli*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void coh901318_lli_free(struct coh901318_pool *pool,
			struct coh901318_lli **lli)
{
	struct coh901318_lli *l;
	struct coh901318_lli *next;

	if (lli == NULL)
		return;

	l = *lli;

	if (l == NULL)
		return;

	spin_lock(&pool->lock);

	while (l->link_addr) {
		next = l->virt_link_addr;
		dma_pool_free(pool->dmapool, l, l->phy_this);
		DEBUGFS_POOL_COUNTER_ADD(pool, -1);
		l = next;
	}
	dma_pool_free(pool->dmapool, l, l->phy_this);
	DEBUGFS_POOL_COUNTER_ADD(pool, -1);

	spin_unlock(&pool->lock);
	*lli = NULL;
}