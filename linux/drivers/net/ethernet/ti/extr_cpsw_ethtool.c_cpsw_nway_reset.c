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
struct cpsw_priv {struct cpsw_common* cpsw; } ;
struct cpsw_common {TYPE_1__* slaves; } ;
struct TYPE_2__ {scalar_t__ phy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int cpsw_slave_index (struct cpsw_common*,struct cpsw_priv*) ; 
 int genphy_restart_aneg (scalar_t__) ; 
 struct cpsw_priv* netdev_priv (struct net_device*) ; 

int cpsw_nway_reset(struct net_device *ndev)
{
	struct cpsw_priv *priv = netdev_priv(ndev);
	struct cpsw_common *cpsw = priv->cpsw;
	int slave_no = cpsw_slave_index(cpsw, priv);

	if (cpsw->slaves[slave_no].phy)
		return genphy_restart_aneg(cpsw->slaves[slave_no].phy);
	else
		return -EOPNOTSUPP;
}