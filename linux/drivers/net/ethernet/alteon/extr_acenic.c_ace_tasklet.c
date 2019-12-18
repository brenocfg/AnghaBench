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
struct net_device {int dummy; } ;
struct ace_private {int version; scalar_t__ tasklet_pending; int /*<<< orphan*/  jumbo_refill_busy; scalar_t__ jumbo; int /*<<< orphan*/  cur_jumbo_bufs; int /*<<< orphan*/  mini_refill_busy; int /*<<< orphan*/  cur_mini_bufs; int /*<<< orphan*/  std_refill_busy; int /*<<< orphan*/  cur_rx_bufs; } ;

/* Variables and functions */
 scalar_t__ RX_JUMBO_SIZE ; 
 int RX_LOW_JUMBO_THRES ; 
 int RX_LOW_MINI_THRES ; 
 int RX_LOW_STD_THRES ; 
 scalar_t__ RX_MINI_SIZE ; 
 scalar_t__ RX_RING_SIZE ; 
 int /*<<< orphan*/  ace_load_jumbo_rx_ring (struct net_device*,scalar_t__) ; 
 int /*<<< orphan*/  ace_load_mini_rx_ring (struct net_device*,scalar_t__) ; 
 int /*<<< orphan*/  ace_load_std_rx_ring (struct net_device*,scalar_t__) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 struct ace_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*,int) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ace_tasklet(unsigned long arg)
{
	struct net_device *dev = (struct net_device *) arg;
	struct ace_private *ap = netdev_priv(dev);
	int cur_size;

	cur_size = atomic_read(&ap->cur_rx_bufs);
	if ((cur_size < RX_LOW_STD_THRES) &&
	    !test_and_set_bit(0, &ap->std_refill_busy)) {
#ifdef DEBUG
		printk("refilling buffers (current %i)\n", cur_size);
#endif
		ace_load_std_rx_ring(dev, RX_RING_SIZE - cur_size);
	}

	if (ap->version >= 2) {
		cur_size = atomic_read(&ap->cur_mini_bufs);
		if ((cur_size < RX_LOW_MINI_THRES) &&
		    !test_and_set_bit(0, &ap->mini_refill_busy)) {
#ifdef DEBUG
			printk("refilling mini buffers (current %i)\n",
			       cur_size);
#endif
			ace_load_mini_rx_ring(dev, RX_MINI_SIZE - cur_size);
		}
	}

	cur_size = atomic_read(&ap->cur_jumbo_bufs);
	if (ap->jumbo && (cur_size < RX_LOW_JUMBO_THRES) &&
	    !test_and_set_bit(0, &ap->jumbo_refill_busy)) {
#ifdef DEBUG
		printk("refilling jumbo buffers (current %i)\n", cur_size);
#endif
		ace_load_jumbo_rx_ring(dev, RX_JUMBO_SIZE - cur_size);
	}
	ap->tasklet_pending = 0;
}