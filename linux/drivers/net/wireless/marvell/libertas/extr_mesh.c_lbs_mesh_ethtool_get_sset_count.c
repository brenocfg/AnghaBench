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
struct net_device {struct lbs_private* ml_priv; } ;
struct lbs_private {struct net_device* mesh_dev; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int ETH_SS_STATS ; 
 int MESH_STATS_NUM ; 

int lbs_mesh_ethtool_get_sset_count(struct net_device *dev, int sset)
{
	struct lbs_private *priv = dev->ml_priv;

	if (sset == ETH_SS_STATS && dev == priv->mesh_dev)
		return MESH_STATS_NUM;

	return -EOPNOTSUPP;
}