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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct enetc_ndev_priv {TYPE_1__* si; } ;
struct TYPE_2__ {int /*<<< orphan*/  num_rss; } ;

/* Variables and functions */
 struct enetc_ndev_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static u32 enetc_get_rxfh_indir_size(struct net_device *ndev)
{
	struct enetc_ndev_priv *priv = netdev_priv(ndev);

	/* return the size of the RX flow hash indirection table */
	return priv->si->num_rss;
}