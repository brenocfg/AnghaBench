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
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  DriverLock; } ;
struct s_smc {TYPE_1__ os; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;
typedef  TYPE_1__ skfddi_priv ;

/* Variables and functions */
 int /*<<< orphan*/  FDDI_K_ALEN ; 
 int /*<<< orphan*/  ResetAdapter (struct s_smc*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct s_smc* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int skfp_ctl_set_mac_address(struct net_device *dev, void *addr)
{
	struct s_smc *smc = netdev_priv(dev);
	struct sockaddr *p_sockaddr = (struct sockaddr *) addr;
	skfddi_priv *bp = &smc->os;
	unsigned long Flags;


	memcpy(dev->dev_addr, p_sockaddr->sa_data, FDDI_K_ALEN);
	spin_lock_irqsave(&bp->DriverLock, Flags);
	ResetAdapter(smc);
	spin_unlock_irqrestore(&bp->DriverLock, Flags);

	return 0;		/* always return zero */
}