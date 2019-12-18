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
typedef  int u8 ;
struct net_device {int dummy; } ;
struct mlx4_en_priv {int dcbx_cap; TYPE_1__* mdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  DCB_CAP_ATTR_DCBX 130 
#define  DCB_CAP_ATTR_PFC 129 
#define  DCB_CAP_ATTR_PFC_TCS 128 
 int mlx4_max_tc (int /*<<< orphan*/ ) ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static u8 mlx4_en_dcbnl_getcap(struct net_device *dev, int capid, u8 *cap)
{
	struct mlx4_en_priv *priv = netdev_priv(dev);

	switch (capid) {
	case DCB_CAP_ATTR_PFC:
		*cap = true;
		break;
	case DCB_CAP_ATTR_DCBX:
		*cap = priv->dcbx_cap;
		break;
	case DCB_CAP_ATTR_PFC_TCS:
		*cap = 1 <<  mlx4_max_tc(priv->mdev->dev);
		break;
	default:
		*cap = false;
		break;
	}

	return 0;
}