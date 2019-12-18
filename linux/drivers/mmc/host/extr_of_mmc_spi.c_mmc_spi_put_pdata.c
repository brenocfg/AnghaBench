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
struct device {int /*<<< orphan*/ * platform_data; struct device_node* of_node; } ;
struct spi_device {struct device dev; } ;
struct of_mmc_spi {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct of_mmc_spi*) ; 
 struct of_mmc_spi* to_of_mmc_spi (struct device*) ; 

void mmc_spi_put_pdata(struct spi_device *spi)
{
	struct device *dev = &spi->dev;
	struct device_node *np = dev->of_node;
	struct of_mmc_spi *oms = to_of_mmc_spi(dev);

	if (!dev->platform_data || !np)
		return;

	kfree(oms);
	dev->platform_data = NULL;
}