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
struct TYPE_2__ {int /*<<< orphan*/ * by_id; int /*<<< orphan*/ * by_hash; int /*<<< orphan*/  lock; } ;
struct ionic_lif {TYPE_1__ rx_filters; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 unsigned int IONIC_RX_FILTER_HLISTS ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int ionic_rx_filters_init(struct ionic_lif *lif)
{
	unsigned int i;

	spin_lock_init(&lif->rx_filters.lock);

	for (i = 0; i < IONIC_RX_FILTER_HLISTS; i++) {
		INIT_HLIST_HEAD(&lif->rx_filters.by_hash[i]);
		INIT_HLIST_HEAD(&lif->rx_filters.by_id[i]);
	}

	return 0;
}