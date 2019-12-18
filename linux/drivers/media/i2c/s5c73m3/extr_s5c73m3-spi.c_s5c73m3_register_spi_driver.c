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
struct TYPE_2__ {int /*<<< orphan*/  of_match_table; int /*<<< orphan*/  name; } ;
struct spi_driver {TYPE_1__ driver; int /*<<< orphan*/  probe; int /*<<< orphan*/  remove; } ;
struct s5c73m3 {struct spi_driver spidrv; } ;

/* Variables and functions */
 int /*<<< orphan*/  S5C73M3_SPI_DRV_NAME ; 
 int /*<<< orphan*/  s5c73m3_spi_ids ; 
 int /*<<< orphan*/  s5c73m3_spi_probe ; 
 int /*<<< orphan*/  s5c73m3_spi_remove ; 
 int spi_register_driver (struct spi_driver*) ; 

int s5c73m3_register_spi_driver(struct s5c73m3 *state)
{
	struct spi_driver *spidrv = &state->spidrv;

	spidrv->remove = s5c73m3_spi_remove;
	spidrv->probe = s5c73m3_spi_probe;
	spidrv->driver.name = S5C73M3_SPI_DRV_NAME;
	spidrv->driver.of_match_table = s5c73m3_spi_ids;

	return spi_register_driver(spidrv);
}