#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  of_node; int /*<<< orphan*/  platform_data; } ;
struct spi_device {int bits_per_word; TYPE_2__ dev; int /*<<< orphan*/  irq; int /*<<< orphan*/  mode; } ;
struct TYPE_6__ {int /*<<< orphan*/  of_node; int /*<<< orphan*/  pdata; int /*<<< orphan*/  ac; int /*<<< orphan*/  irq; int /*<<< orphan*/  write; int /*<<< orphan*/  read; int /*<<< orphan*/  init; struct spi_device* bus_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPI_MODE_0 ; 
 int /*<<< orphan*/  lis302dl_spi_dt_ids ; 
 TYPE_1__ lis3_dev ; 
 int /*<<< orphan*/  lis3_spi_init ; 
 int /*<<< orphan*/  lis3_spi_read ; 
 int /*<<< orphan*/  lis3_spi_write ; 
 int /*<<< orphan*/  lis3lv02d_axis_normal ; 
 int lis3lv02d_init_device (TYPE_1__*) ; 
 int lis3lv02d_init_dt (TYPE_1__*) ; 
 scalar_t__ of_match_device (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,TYPE_1__*) ; 
 int spi_setup (struct spi_device*) ; 

__attribute__((used)) static int lis302dl_spi_probe(struct spi_device *spi)
{
	int ret;

	spi->bits_per_word = 8;
	spi->mode = SPI_MODE_0;
	ret = spi_setup(spi);
	if (ret < 0)
		return ret;

	lis3_dev.bus_priv	= spi;
	lis3_dev.init		= lis3_spi_init;
	lis3_dev.read		= lis3_spi_read;
	lis3_dev.write		= lis3_spi_write;
	lis3_dev.irq		= spi->irq;
	lis3_dev.ac		= lis3lv02d_axis_normal;
	lis3_dev.pdata		= spi->dev.platform_data;

#ifdef CONFIG_OF
	if (of_match_device(lis302dl_spi_dt_ids, &spi->dev)) {
		lis3_dev.of_node = spi->dev.of_node;
		ret = lis3lv02d_init_dt(&lis3_dev);
		if (ret)
			return ret;
	}
#endif
	spi_set_drvdata(spi, &lis3_dev);

	return lis3lv02d_init_device(&lis3_dev);
}