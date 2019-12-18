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
struct encx24j600_priv {int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 struct encx24j600_priv* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_netdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int encx24j600_spi_remove(struct spi_device *spi)
{
	struct encx24j600_priv *priv = dev_get_drvdata(&spi->dev);

	unregister_netdev(priv->ndev);

	free_netdev(priv->ndev);

	return 0;
}