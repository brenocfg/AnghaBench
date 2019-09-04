#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct device* parent; } ;
struct platform_device {TYPE_2__ dev; } ;
struct net_device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  cgrid; } ;
struct TYPE_4__ {TYPE_3__ cgr; } ;
struct dpaa_priv {TYPE_1__ cgr_data; TYPE_3__ ingress_cgr; int /*<<< orphan*/  dpaa_fq_list; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct net_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dpaa_bps_free (struct dpaa_priv*) ; 
 int /*<<< orphan*/  dpaa_eth_sysfs_remove (struct device*) ; 
 int dpaa_fq_free (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dpaa_napi_del (struct net_device*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 struct dpaa_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  qman_delete_cgr_safe (TYPE_3__*) ; 
 int /*<<< orphan*/  qman_release_cgrid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int dpaa_remove(struct platform_device *pdev)
{
	struct net_device *net_dev;
	struct dpaa_priv *priv;
	struct device *dev;
	int err;

	dev = pdev->dev.parent;
	net_dev = dev_get_drvdata(dev);

	priv = netdev_priv(net_dev);

	dpaa_eth_sysfs_remove(dev);

	dev_set_drvdata(dev, NULL);
	unregister_netdev(net_dev);

	err = dpaa_fq_free(dev, &priv->dpaa_fq_list);

	qman_delete_cgr_safe(&priv->ingress_cgr);
	qman_release_cgrid(priv->ingress_cgr.cgrid);
	qman_delete_cgr_safe(&priv->cgr_data.cgr);
	qman_release_cgrid(priv->cgr_data.cgr.cgrid);

	dpaa_napi_del(net_dev);

	dpaa_bps_free(priv);

	free_netdev(net_dev);

	return err;
}