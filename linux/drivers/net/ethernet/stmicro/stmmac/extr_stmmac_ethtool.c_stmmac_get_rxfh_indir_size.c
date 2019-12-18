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
struct TYPE_2__ {int /*<<< orphan*/  table; } ;
struct stmmac_priv {TYPE_1__ rss; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 struct stmmac_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static u32 stmmac_get_rxfh_indir_size(struct net_device *dev)
{
	struct stmmac_priv *priv = netdev_priv(dev);

	return ARRAY_SIZE(priv->rss.table);
}