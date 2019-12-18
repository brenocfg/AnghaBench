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
struct spi_device {int /*<<< orphan*/  dev; } ;
struct ks8851_net {int /*<<< orphan*/  netdev; int /*<<< orphan*/  vdd_io; int /*<<< orphan*/  vdd_reg; int /*<<< orphan*/  gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free_netdev (int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ netif_msg_drv (struct ks8851_net*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 struct ks8851_net* spi_get_drvdata (struct spi_device*) ; 
 int /*<<< orphan*/  unregister_netdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ks8851_remove(struct spi_device *spi)
{
	struct ks8851_net *priv = spi_get_drvdata(spi);

	if (netif_msg_drv(priv))
		dev_info(&spi->dev, "remove\n");

	unregister_netdev(priv->netdev);
	if (gpio_is_valid(priv->gpio))
		gpio_set_value(priv->gpio, 0);
	regulator_disable(priv->vdd_reg);
	regulator_disable(priv->vdd_io);
	free_netdev(priv->netdev);

	return 0;
}