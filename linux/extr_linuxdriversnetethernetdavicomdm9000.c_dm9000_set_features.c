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
struct net_device {int features; } ;
struct board_info {int /*<<< orphan*/  lock; } ;
typedef  int netdev_features_t ;

/* Variables and functions */
 int /*<<< orphan*/  DM9000_RCSR ; 
 int NETIF_F_RXCSUM ; 
 int /*<<< orphan*/  RCSR_CSUM ; 
 int /*<<< orphan*/  iow (struct board_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct board_info* to_dm9000_board (struct net_device*) ; 

__attribute__((used)) static int dm9000_set_features(struct net_device *dev,
	netdev_features_t features)
{
	struct board_info *dm = to_dm9000_board(dev);
	netdev_features_t changed = dev->features ^ features;
	unsigned long flags;

	if (!(changed & NETIF_F_RXCSUM))
		return 0;

	spin_lock_irqsave(&dm->lock, flags);
	iow(dm, DM9000_RCSR, (features & NETIF_F_RXCSUM) ? RCSR_CSUM : 0);
	spin_unlock_irqrestore(&dm->lock, flags);

	return 0;
}