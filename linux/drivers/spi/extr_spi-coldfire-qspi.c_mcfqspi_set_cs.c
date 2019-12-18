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
struct spi_device {int mode; int /*<<< orphan*/  chip_select; int /*<<< orphan*/  master; } ;
struct mcfqspi {int dummy; } ;

/* Variables and functions */
 int SPI_CS_HIGH ; 
 int /*<<< orphan*/  mcfqspi_cs_deselect (struct mcfqspi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mcfqspi_cs_select (struct mcfqspi*,int /*<<< orphan*/ ,int) ; 
 struct mcfqspi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mcfqspi_set_cs(struct spi_device *spi, bool enable)
{
	struct mcfqspi *mcfqspi = spi_master_get_devdata(spi->master);
	bool cs_high = spi->mode & SPI_CS_HIGH;

	if (enable)
		mcfqspi_cs_select(mcfqspi, spi->chip_select, cs_high);
	else
		mcfqspi_cs_deselect(mcfqspi, spi->chip_select, cs_high);
}