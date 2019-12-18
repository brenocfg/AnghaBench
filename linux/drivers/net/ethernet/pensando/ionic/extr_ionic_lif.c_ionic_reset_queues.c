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
struct ionic_lif {int /*<<< orphan*/  state; int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  IONIC_LIF_QUEUE_RESET ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ionic_open (int /*<<< orphan*/ ) ; 
 int ionic_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ionic_wait_for_bit (struct ionic_lif*,int /*<<< orphan*/ ) ; 
 int netif_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_trans_update (int /*<<< orphan*/ ) ; 

int ionic_reset_queues(struct ionic_lif *lif)
{
	bool running;
	int err = 0;

	/* Put off the next watchdog timeout */
	netif_trans_update(lif->netdev);

	if (!ionic_wait_for_bit(lif, IONIC_LIF_QUEUE_RESET))
		return -EBUSY;

	running = netif_running(lif->netdev);
	if (running)
		err = ionic_stop(lif->netdev);
	if (!err && running)
		ionic_open(lif->netdev);

	clear_bit(IONIC_LIF_QUEUE_RESET, lif->state);

	return err;
}