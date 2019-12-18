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
struct net_device {int flags; } ;
struct dmfe_board_info {int cr6_data; scalar_t__ chip_id; int /*<<< orphan*/  lock; int /*<<< orphan*/  ioaddr; } ;

/* Variables and functions */
 int CR6_PAM ; 
 int CR6_PBF ; 
 int CR6_PM ; 
 int /*<<< orphan*/  DMFE_DBUG (int /*<<< orphan*/ ,char*,int) ; 
 int DMFE_MAX_MULTICAST ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 scalar_t__ PCI_DM9132_ID ; 
 int /*<<< orphan*/  dm9132_id_table (struct net_device*) ; 
 int netdev_mc_count (struct net_device*) ; 
 struct dmfe_board_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  send_filter_frame (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  update_cr6 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dmfe_set_filter_mode(struct net_device *dev)
{
	struct dmfe_board_info *db = netdev_priv(dev);
	unsigned long flags;
	int mc_count = netdev_mc_count(dev);

	DMFE_DBUG(0, "dmfe_set_filter_mode()", 0);
	spin_lock_irqsave(&db->lock, flags);

	if (dev->flags & IFF_PROMISC) {
		DMFE_DBUG(0, "Enable PROM Mode", 0);
		db->cr6_data |= CR6_PM | CR6_PBF;
		update_cr6(db->cr6_data, db->ioaddr);
		spin_unlock_irqrestore(&db->lock, flags);
		return;
	}

	if (dev->flags & IFF_ALLMULTI || mc_count > DMFE_MAX_MULTICAST) {
		DMFE_DBUG(0, "Pass all multicast address", mc_count);
		db->cr6_data &= ~(CR6_PM | CR6_PBF);
		db->cr6_data |= CR6_PAM;
		spin_unlock_irqrestore(&db->lock, flags);
		return;
	}

	DMFE_DBUG(0, "Set multicast address", mc_count);
	if (db->chip_id == PCI_DM9132_ID)
		dm9132_id_table(dev);	/* DM9132 */
	else
		send_filter_frame(dev);	/* DM9102/DM9102A */
	spin_unlock_irqrestore(&db->lock, flags);
}