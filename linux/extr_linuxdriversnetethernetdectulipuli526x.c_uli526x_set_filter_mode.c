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
struct uli526x_board_info {int cr6_data; int /*<<< orphan*/  lock; int /*<<< orphan*/  ioaddr; } ;
struct net_device {int flags; } ;

/* Variables and functions */
 int CR6_PAM ; 
 int CR6_PBF ; 
 int CR6_PM ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 scalar_t__ ULI5261_MAX_MULTICAST ; 
 int /*<<< orphan*/  ULI526X_DBUG (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ netdev_mc_count (struct net_device*) ; 
 struct uli526x_board_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  send_filter_frame (struct net_device*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  update_cr6 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uli526x_set_filter_mode(struct net_device * dev)
{
	struct uli526x_board_info *db = netdev_priv(dev);
	unsigned long flags;

	ULI526X_DBUG(0, "uli526x_set_filter_mode()", 0);
	spin_lock_irqsave(&db->lock, flags);

	if (dev->flags & IFF_PROMISC) {
		ULI526X_DBUG(0, "Enable PROM Mode", 0);
		db->cr6_data |= CR6_PM | CR6_PBF;
		update_cr6(db->cr6_data, db->ioaddr);
		spin_unlock_irqrestore(&db->lock, flags);
		return;
	}

	if (dev->flags & IFF_ALLMULTI ||
	    netdev_mc_count(dev) > ULI5261_MAX_MULTICAST) {
		ULI526X_DBUG(0, "Pass all multicast address",
			     netdev_mc_count(dev));
		db->cr6_data &= ~(CR6_PM | CR6_PBF);
		db->cr6_data |= CR6_PAM;
		spin_unlock_irqrestore(&db->lock, flags);
		return;
	}

	ULI526X_DBUG(0, "Set multicast address", netdev_mc_count(dev));
	send_filter_frame(dev, netdev_mc_count(dev)); 	/* M5261/M5263 */
	spin_unlock_irqrestore(&db->lock, flags);
}