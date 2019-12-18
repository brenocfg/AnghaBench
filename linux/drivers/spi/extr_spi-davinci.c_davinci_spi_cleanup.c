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
struct TYPE_2__ {scalar_t__ of_node; } ;
struct spi_device {TYPE_1__ dev; struct davinci_spi_config* controller_data; } ;
struct davinci_spi_config {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct davinci_spi_config*) ; 

__attribute__((used)) static void davinci_spi_cleanup(struct spi_device *spi)
{
	struct davinci_spi_config *spicfg = spi->controller_data;

	spi->controller_data = NULL;
	if (spi->dev.of_node)
		kfree(spicfg);
}