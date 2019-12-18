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
struct ieee_ets {int /*<<< orphan*/  prio_tc; int /*<<< orphan*/  tc_tsa; int /*<<< orphan*/  tc_tx_bw; int /*<<< orphan*/  cbs; int /*<<< orphan*/  ets_cap; } ;
struct mlx4_en_priv {struct ieee_ets ets; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IEEE_8021QAZ_MAX_TCS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mlx4_en_dcbnl_ieee_getets(struct net_device *dev,
				   struct ieee_ets *ets)
{
	struct mlx4_en_priv *priv = netdev_priv(dev);
	struct ieee_ets *my_ets = &priv->ets;

	if (!my_ets)
		return -EINVAL;

	ets->ets_cap = IEEE_8021QAZ_MAX_TCS;
	ets->cbs = my_ets->cbs;
	memcpy(ets->tc_tx_bw, my_ets->tc_tx_bw, sizeof(ets->tc_tx_bw));
	memcpy(ets->tc_tsa, my_ets->tc_tsa, sizeof(ets->tc_tsa));
	memcpy(ets->prio_tc, my_ets->prio_tc, sizeof(ets->prio_tc));

	return 0;
}