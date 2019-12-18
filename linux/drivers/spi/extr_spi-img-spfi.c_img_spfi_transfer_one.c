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
struct spi_master {scalar_t__ (* can_dma ) (struct spi_master*,struct spi_device*,struct spi_transfer*) ;} ;
struct spi_device {int /*<<< orphan*/  master; } ;
struct img_spfi {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SPFI_TRANSACTION_TSIZE_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  img_spfi_config (struct spi_master*,struct spi_device*,struct spi_transfer*) ; 
 int img_spfi_start_dma (struct spi_master*,struct spi_device*,struct spi_transfer*) ; 
 int img_spfi_start_pio (struct spi_master*,struct spi_device*,struct spi_transfer*) ; 
 struct img_spfi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct spi_master*,struct spi_device*,struct spi_transfer*) ; 

__attribute__((used)) static int img_spfi_transfer_one(struct spi_master *master,
				 struct spi_device *spi,
				 struct spi_transfer *xfer)
{
	struct img_spfi *spfi = spi_master_get_devdata(spi->master);
	int ret;

	if (xfer->len > SPFI_TRANSACTION_TSIZE_MASK) {
		dev_err(spfi->dev,
			"Transfer length (%d) is greater than the max supported (%d)",
			xfer->len, SPFI_TRANSACTION_TSIZE_MASK);
		return -EINVAL;
	}

	img_spfi_config(master, spi, xfer);
	if (master->can_dma && master->can_dma(master, spi, xfer))
		ret = img_spfi_start_dma(master, spi, xfer);
	else
		ret = img_spfi_start_pio(master, spi, xfer);

	return ret;
}