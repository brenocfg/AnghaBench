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
struct enc28j60_net {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct enc28j60_net*) ; 
 int /*<<< orphan*/  free_netdev (int /*<<< orphan*/ ) ; 
 struct enc28j60_net* spi_get_drvdata (struct spi_device*) ; 
 int /*<<< orphan*/  unregister_netdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int enc28j60_remove(struct spi_device *spi)
{
	struct enc28j60_net *priv = spi_get_drvdata(spi);

	unregister_netdev(priv->netdev);
	free_irq(spi->irq, priv);
	free_netdev(priv->netdev);

	return 0;
}