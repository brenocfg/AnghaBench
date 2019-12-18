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
struct stmmac_priv {TYPE_1__* dev; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  netdev_warn (TYPE_1__*,char*) ; 

__attribute__((used)) static int stmmac_filter_check(struct stmmac_priv *priv)
{
	if (!(priv->dev->flags & IFF_PROMISC))
		return 0;

	netdev_warn(priv->dev, "Test can't be run in promiscuous mode!\n");
	return -EOPNOTSUPP;
}