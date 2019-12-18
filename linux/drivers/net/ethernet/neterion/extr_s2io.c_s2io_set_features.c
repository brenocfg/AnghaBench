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
struct s2io_nic {int dummy; } ;
struct net_device {int features; } ;
typedef  int netdev_features_t ;

/* Variables and functions */
 int NETIF_F_LRO ; 
 struct s2io_nic* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  s2io_card_down (struct s2io_nic*) ; 
 int s2io_card_up (struct s2io_nic*) ; 
 int /*<<< orphan*/  s2io_reset (struct s2io_nic*) ; 
 int /*<<< orphan*/  s2io_start_all_tx_queue (struct s2io_nic*) ; 
 int /*<<< orphan*/  s2io_stop_all_tx_queue (struct s2io_nic*) ; 

__attribute__((used)) static int s2io_set_features(struct net_device *dev, netdev_features_t features)
{
	struct s2io_nic *sp = netdev_priv(dev);
	netdev_features_t changed = (features ^ dev->features) & NETIF_F_LRO;

	if (changed && netif_running(dev)) {
		int rc;

		s2io_stop_all_tx_queue(sp);
		s2io_card_down(sp);
		dev->features = features;
		rc = s2io_card_up(sp);
		if (rc)
			s2io_reset(sp);
		else
			s2io_start_all_tx_queue(sp);

		return rc ? rc : 1;
	}

	return 0;
}