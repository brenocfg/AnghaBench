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
struct cpsw_priv {TYPE_1__* cpsw; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpsw_err (struct cpsw_priv*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  drv ; 
 struct cpsw_priv* netdev_priv (struct net_device*) ; 
 int pm_runtime_put (int /*<<< orphan*/ ) ; 

void cpsw_ethtool_op_complete(struct net_device *ndev)
{
	struct cpsw_priv *priv = netdev_priv(ndev);
	int ret;

	ret = pm_runtime_put(priv->cpsw->dev);
	if (ret < 0)
		cpsw_err(priv, drv, "ethtool complete failed %d\n", ret);
}