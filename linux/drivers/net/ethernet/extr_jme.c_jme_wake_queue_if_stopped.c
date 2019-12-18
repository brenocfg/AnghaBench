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
struct jme_ring {int /*<<< orphan*/  nr_free; } ;
struct jme_adapter {scalar_t__ tx_wake_threshold; int /*<<< orphan*/  dev; struct jme_ring* txring; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_info (struct jme_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ netif_queue_stopped (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  tx_done ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
jme_wake_queue_if_stopped(struct jme_adapter *jme)
{
	struct jme_ring *txring = &(jme->txring[0]);

	smp_wmb();
	if (unlikely(netif_queue_stopped(jme->dev) &&
	atomic_read(&txring->nr_free) >= (jme->tx_wake_threshold))) {
		netif_info(jme, tx_done, jme->dev, "TX Queue Waked\n");
		netif_wake_queue(jme->dev);
	}

}