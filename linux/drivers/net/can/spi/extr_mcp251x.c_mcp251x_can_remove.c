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
struct spi_device {int dummy; } ;
struct net_device {int dummy; } ;
struct mcp251x_priv {int /*<<< orphan*/  clk; int /*<<< orphan*/  power; struct net_device* net; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_candev (struct net_device*) ; 
 int /*<<< orphan*/  mcp251x_power_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mcp251x_priv* spi_get_drvdata (struct spi_device*) ; 
 int /*<<< orphan*/  unregister_candev (struct net_device*) ; 

__attribute__((used)) static int mcp251x_can_remove(struct spi_device *spi)
{
	struct mcp251x_priv *priv = spi_get_drvdata(spi);
	struct net_device *net = priv->net;

	unregister_candev(net);

	mcp251x_power_enable(priv->power, 0);

	clk_disable_unprepare(priv->clk);

	free_candev(net);

	return 0;
}