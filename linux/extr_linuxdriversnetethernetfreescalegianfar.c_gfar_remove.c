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
struct TYPE_2__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct gfar_private {int /*<<< orphan*/  ndev; int /*<<< orphan*/  tbi_node; int /*<<< orphan*/  phy_node; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_gfar_dev (struct gfar_private*) ; 
 int /*<<< orphan*/  gfar_free_rx_queues (struct gfar_private*) ; 
 int /*<<< orphan*/  gfar_free_tx_queues (struct gfar_private*) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_phy_deregister_fixed_link (struct device_node*) ; 
 scalar_t__ of_phy_is_fixed_link (struct device_node*) ; 
 struct gfar_private* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  unmap_group_regs (struct gfar_private*) ; 
 int /*<<< orphan*/  unregister_netdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gfar_remove(struct platform_device *ofdev)
{
	struct gfar_private *priv = platform_get_drvdata(ofdev);
	struct device_node *np = ofdev->dev.of_node;

	of_node_put(priv->phy_node);
	of_node_put(priv->tbi_node);

	unregister_netdev(priv->ndev);

	if (of_phy_is_fixed_link(np))
		of_phy_deregister_fixed_link(np);

	unmap_group_regs(priv);
	gfar_free_rx_queues(priv);
	gfar_free_tx_queues(priv);
	free_gfar_dev(priv);

	return 0;
}