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
typedef  int /*<<< orphan*/  u8 ;
struct spi_transfer {int /*<<< orphan*/  len; int /*<<< orphan*/  rx_buf; int /*<<< orphan*/  tx_buf; int /*<<< orphan*/  cs_change; int /*<<< orphan*/  bits_per_word; int /*<<< orphan*/  speed_hz; } ;
struct spi_master {int dummy; } ;
struct spi_device {int /*<<< orphan*/  mode; } ;
struct dln2_spi {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLN2_SPI_ATTR_LEAVE_SS_LOW ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int dln2_spi_rdwr (struct dln2_spi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dln2_spi_transfer_setup (struct dln2_spi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dln2_spi* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  spi_transfer_is_last (struct spi_master*,struct spi_transfer*) ; 

__attribute__((used)) static int dln2_spi_transfer_one(struct spi_master *master,
				 struct spi_device *spi,
				 struct spi_transfer *xfer)
{
	struct dln2_spi *dln2 = spi_master_get_devdata(master);
	int status;
	u8 attr = 0;

	status = dln2_spi_transfer_setup(dln2, xfer->speed_hz,
					 xfer->bits_per_word,
					 spi->mode);
	if (status < 0) {
		dev_err(&dln2->pdev->dev, "Cannot setup transfer\n");
		return status;
	}

	if (!xfer->cs_change && !spi_transfer_is_last(master, xfer))
		attr = DLN2_SPI_ATTR_LEAVE_SS_LOW;

	status = dln2_spi_rdwr(dln2, xfer->tx_buf, xfer->rx_buf,
			       xfer->len, attr);
	if (status < 0)
		dev_err(&dln2->pdev->dev, "write/read failed!\n");

	return status;
}