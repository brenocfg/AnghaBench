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
typedef  int /*<<< orphan*/  netdev_features_t ;

/* Variables and functions */
 int /*<<< orphan*/  NETIF_F_HW_TC ; 
 int /*<<< orphan*/  mlxsw_sp_feature_hw_tc ; 
 int mlxsw_sp_handle_feature (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlxsw_sp_set_features(struct net_device *dev,
				 netdev_features_t features)
{
	return mlxsw_sp_handle_feature(dev, features, NETIF_F_HW_TC,
				       mlxsw_sp_feature_hw_tc);
}