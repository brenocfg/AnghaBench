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
struct cpsw_priv {struct cpsw_common* cpsw; } ;
struct cpsw_common {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpsw_err (struct cpsw_priv*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  drv ; 
 struct cpsw_priv* netdev_priv (struct net_device*) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ ) ; 

int cpsw_ethtool_op_begin(struct net_device *ndev)
{
	struct cpsw_priv *priv = netdev_priv(ndev);
	struct cpsw_common *cpsw = priv->cpsw;
	int ret;

	ret = pm_runtime_get_sync(cpsw->dev);
	if (ret < 0) {
		cpsw_err(priv, drv, "ethtool begin failed %d\n", ret);
		pm_runtime_put_noidle(cpsw->dev);
	}

	return ret;
}