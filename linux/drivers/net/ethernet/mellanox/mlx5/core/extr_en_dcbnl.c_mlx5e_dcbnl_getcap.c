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
struct TYPE_2__ {int cap; } ;
struct mlx5e_priv {TYPE_1__ dcbx; struct mlx5_core_dev* mdev; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
#define  DCB_CAP_ATTR_BCN 135 
#define  DCB_CAP_ATTR_DCBX 134 
#define  DCB_CAP_ATTR_GSP 133 
#define  DCB_CAP_ATTR_PFC 132 
#define  DCB_CAP_ATTR_PFC_TCS 131 
#define  DCB_CAP_ATTR_PG 130 
#define  DCB_CAP_ATTR_PG_TCS 129 
#define  DCB_CAP_ATTR_UP2TC 128 
 int DCB_CAP_DCBX_VER_CEE ; 
 int DCB_CAP_DCBX_VER_IEEE ; 
 int mlx5_max_tc (struct mlx5_core_dev*) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static u8 mlx5e_dcbnl_getcap(struct net_device *netdev,
			     int capid, u8 *cap)
{
	struct mlx5e_priv *priv = netdev_priv(netdev);
	struct mlx5_core_dev *mdev = priv->mdev;
	u8 rval = 0;

	switch (capid) {
	case DCB_CAP_ATTR_PG:
		*cap = true;
		break;
	case DCB_CAP_ATTR_PFC:
		*cap = true;
		break;
	case DCB_CAP_ATTR_UP2TC:
		*cap = false;
		break;
	case DCB_CAP_ATTR_PG_TCS:
		*cap = 1 << mlx5_max_tc(mdev);
		break;
	case DCB_CAP_ATTR_PFC_TCS:
		*cap = 1 << mlx5_max_tc(mdev);
		break;
	case DCB_CAP_ATTR_GSP:
		*cap = false;
		break;
	case DCB_CAP_ATTR_BCN:
		*cap = false;
		break;
	case DCB_CAP_ATTR_DCBX:
		*cap = priv->dcbx.cap |
		       DCB_CAP_DCBX_VER_CEE |
		       DCB_CAP_DCBX_VER_IEEE;
		break;
	default:
		*cap = 0;
		rval = 1;
		break;
	}

	return rval;
}