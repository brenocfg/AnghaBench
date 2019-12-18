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
struct platform_device {int dummy; } ;
struct net_device {int /*<<< orphan*/  irq; } ;
struct mvneta_port {int id; scalar_t__ bm_priv; int /*<<< orphan*/  pool_short; int /*<<< orphan*/  pool_long; int /*<<< orphan*/  phylink; int /*<<< orphan*/  stats; int /*<<< orphan*/  ports; int /*<<< orphan*/  clk; int /*<<< orphan*/  clk_bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_dispose_mapping (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvneta_bm_pool_destroy (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mvneta_bm_put (scalar_t__) ; 
 struct mvneta_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  phylink_destroy (int /*<<< orphan*/ ) ; 
 struct net_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int mvneta_remove(struct platform_device *pdev)
{
	struct net_device  *dev = platform_get_drvdata(pdev);
	struct mvneta_port *pp = netdev_priv(dev);

	unregister_netdev(dev);
	clk_disable_unprepare(pp->clk_bus);
	clk_disable_unprepare(pp->clk);
	free_percpu(pp->ports);
	free_percpu(pp->stats);
	irq_dispose_mapping(dev->irq);
	phylink_destroy(pp->phylink);

	if (pp->bm_priv) {
		mvneta_bm_pool_destroy(pp->bm_priv, pp->pool_long, 1 << pp->id);
		mvneta_bm_pool_destroy(pp->bm_priv, pp->pool_short,
				       1 << pp->id);
		mvneta_bm_put(pp->bm_priv);
	}

	return 0;
}