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
typedef  int u8 ;
struct net_device {int dummy; } ;
struct mlx4_en_priv {int dcbx_cap; } ;
struct ieee_pfc {void* pfc_cap; int /*<<< orphan*/  member_0; } ;
struct ieee_ets {void* ets_cap; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int DCB_CAP_DCBX_HOST ; 
 int DCB_CAP_DCBX_LLD_MANAGED ; 
 int DCB_CAP_DCBX_VER_CEE ; 
 int DCB_CAP_DCBX_VER_IEEE ; 
 void* IEEE_8021QAZ_MAX_TCS ; 
 scalar_t__ mlx4_en_alloc_tx_queue_per_tc (struct net_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ mlx4_en_dcbnl_ieee_setets (struct net_device*,struct ieee_ets*) ; 
 scalar_t__ mlx4_en_dcbnl_ieee_setpfc (struct net_device*,struct ieee_pfc*) ; 
 scalar_t__ mlx4_en_dcbnl_set_all (struct net_device*) ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static u8 mlx4_en_dcbnl_setdcbx(struct net_device *dev, u8 mode)
{
	struct mlx4_en_priv *priv = netdev_priv(dev);
	struct ieee_ets ets = {0};
	struct ieee_pfc pfc = {0};

	if (mode == priv->dcbx_cap)
		return 0;

	if ((mode & DCB_CAP_DCBX_LLD_MANAGED) ||
	    ((mode & DCB_CAP_DCBX_VER_IEEE) &&
	     (mode & DCB_CAP_DCBX_VER_CEE)) ||
	    !(mode & DCB_CAP_DCBX_HOST))
		goto err;

	priv->dcbx_cap = mode;

	ets.ets_cap = IEEE_8021QAZ_MAX_TCS;
	pfc.pfc_cap = IEEE_8021QAZ_MAX_TCS;

	if (mode & DCB_CAP_DCBX_VER_IEEE) {
		if (mlx4_en_dcbnl_ieee_setets(dev, &ets))
			goto err;
		if (mlx4_en_dcbnl_ieee_setpfc(dev, &pfc))
			goto err;
	} else if (mode & DCB_CAP_DCBX_VER_CEE) {
		if (mlx4_en_dcbnl_set_all(dev))
			goto err;
	} else {
		if (mlx4_en_dcbnl_ieee_setets(dev, &ets))
			goto err;
		if (mlx4_en_dcbnl_ieee_setpfc(dev, &pfc))
			goto err;
		if (mlx4_en_alloc_tx_queue_per_tc(dev, 0))
			goto err;
	}

	return 0;
err:
	return 1;
}