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
struct spi_transfer {int /*<<< orphan*/  len; } ;
struct spi_master {int dummy; } ;
struct spi_geni_master {int dummy; } ;
struct spi_device {int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  setup_fifo_xfer (struct spi_transfer*,struct spi_geni_master*,int /*<<< orphan*/ ,struct spi_master*) ; 
 struct spi_geni_master* spi_master_get_devdata (struct spi_master*) ; 

__attribute__((used)) static int spi_geni_transfer_one(struct spi_master *spi,
				struct spi_device *slv,
				struct spi_transfer *xfer)
{
	struct spi_geni_master *mas = spi_master_get_devdata(spi);

	/* Terminate and return success for 0 byte length transfer */
	if (!xfer->len)
		return 0;

	setup_fifo_xfer(xfer, mas, slv->mode, spi);
	return 1;
}