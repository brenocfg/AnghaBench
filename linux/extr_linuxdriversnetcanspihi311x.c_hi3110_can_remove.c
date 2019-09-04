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
struct hi3110_priv {int /*<<< orphan*/  clk; int /*<<< orphan*/  power; struct net_device* net; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_candev (struct net_device*) ; 
 int /*<<< orphan*/  hi3110_power_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hi3110_priv* spi_get_drvdata (struct spi_device*) ; 
 int /*<<< orphan*/  unregister_candev (struct net_device*) ; 

__attribute__((used)) static int hi3110_can_remove(struct spi_device *spi)
{
	struct hi3110_priv *priv = spi_get_drvdata(spi);
	struct net_device *net = priv->net;

	unregister_candev(net);

	hi3110_power_enable(priv->power, 0);

	if (!IS_ERR(priv->clk))
		clk_disable_unprepare(priv->clk);

	free_candev(net);

	return 0;
}