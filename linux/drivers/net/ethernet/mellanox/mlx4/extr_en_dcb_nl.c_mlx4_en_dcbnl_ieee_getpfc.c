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
struct net_device {int dummy; } ;
struct mlx4_en_priv {TYPE_1__* prof; } ;
struct ieee_pfc {int /*<<< orphan*/  pfc_en; int /*<<< orphan*/  pfc_cap; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_ppp; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE_8021QAZ_MAX_TCS ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mlx4_en_dcbnl_ieee_getpfc(struct net_device *dev,
		struct ieee_pfc *pfc)
{
	struct mlx4_en_priv *priv = netdev_priv(dev);

	pfc->pfc_cap = IEEE_8021QAZ_MAX_TCS;
	pfc->pfc_en = priv->prof->tx_ppp;

	return 0;
}