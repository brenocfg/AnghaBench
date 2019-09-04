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
struct spi_device {int /*<<< orphan*/  irq; } ;
struct net_device {int dummy; } ;
struct mcp251x_priv {int /*<<< orphan*/  transceiver; struct spi_device* spi; } ;

/* Variables and functions */
 int /*<<< orphan*/  close_candev (struct net_device*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct mcp251x_priv*) ; 
 int /*<<< orphan*/  mcp251x_hw_sleep (struct spi_device*) ; 
 int /*<<< orphan*/  mcp251x_power_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mcp251x_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void mcp251x_open_clean(struct net_device *net)
{
	struct mcp251x_priv *priv = netdev_priv(net);
	struct spi_device *spi = priv->spi;

	free_irq(spi->irq, priv);
	mcp251x_hw_sleep(spi);
	mcp251x_power_enable(priv->transceiver, 0);
	close_candev(net);
}