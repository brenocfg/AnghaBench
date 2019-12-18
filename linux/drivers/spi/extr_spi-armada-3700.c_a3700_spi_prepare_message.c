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
struct spi_message {struct spi_device* spi; } ;
struct spi_master {int dummy; } ;
struct spi_device {int /*<<< orphan*/  mode; int /*<<< orphan*/  dev; } ;
struct a3700_spi {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int a3700_spi_fifo_flush (struct a3700_spi*) ; 
 int /*<<< orphan*/  a3700_spi_mode_set (struct a3700_spi*,int /*<<< orphan*/ ) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct a3700_spi* spi_master_get_devdata (struct spi_master*) ; 

__attribute__((used)) static int a3700_spi_prepare_message(struct spi_master *master,
				     struct spi_message *message)
{
	struct a3700_spi *a3700_spi = spi_master_get_devdata(master);
	struct spi_device *spi = message->spi;
	int ret;

	ret = clk_enable(a3700_spi->clk);
	if (ret) {
		dev_err(&spi->dev, "failed to enable clk with error %d\n", ret);
		return ret;
	}

	/* Flush the FIFOs */
	ret = a3700_spi_fifo_flush(a3700_spi);
	if (ret)
		return ret;

	a3700_spi_mode_set(a3700_spi, spi->mode);

	return 0;
}