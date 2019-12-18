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
struct net_device {int /*<<< orphan*/  irq; struct airo_info* ml_priv; } ;
struct airo_info {int /*<<< orphan*/  airo_thread_task; int /*<<< orphan*/  jobs; int /*<<< orphan*/  flags; struct net_device* wifidev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_RADIO_DOWN ; 
 int /*<<< orphan*/  JOB_DIE ; 
 int /*<<< orphan*/  disable_MAC (struct airo_info*,int) ; 
 int /*<<< orphan*/  disable_interrupts (struct airo_info*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int airo_close(struct net_device *dev) {
	struct airo_info *ai = dev->ml_priv;

	netif_stop_queue(dev);

	if (ai->wifidev != dev) {
#ifdef POWER_ON_DOWN
		/* Shut power to the card. The idea is that the user can save
		 * power when he doesn't need the card with "ifconfig down".
		 * That's the method that is most friendly towards the network
		 * stack (i.e. the network stack won't try to broadcast
		 * anything on the interface and routes are gone. Jean II */
		set_bit(FLAG_RADIO_DOWN, &ai->flags);
		disable_MAC(ai, 1);
#endif
		disable_interrupts( ai );

		free_irq(dev->irq, dev);

		set_bit(JOB_DIE, &ai->jobs);
		kthread_stop(ai->airo_thread_task);
	}
	return 0;
}