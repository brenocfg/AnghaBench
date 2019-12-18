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
struct tegra_spi_client_data {int dummy; } ;
struct TYPE_2__ {scalar_t__ of_node; } ;
struct spi_device {TYPE_1__ dev; struct tegra_spi_client_data* controller_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct tegra_spi_client_data*) ; 

__attribute__((used)) static void tegra_spi_cleanup(struct spi_device *spi)
{
	struct tegra_spi_client_data *cdata = spi->controller_data;

	spi->controller_data = NULL;
	if (spi->dev.of_node)
		kfree(cdata);
}