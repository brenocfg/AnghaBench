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
struct spi_device {int mode; int /*<<< orphan*/  cs_gpio; void* controller_data; int /*<<< orphan*/  master; } ;
struct mtk_spi {TYPE_1__* dev_comp; } ;
struct TYPE_2__ {scalar_t__ need_pad_sel; } ;

/* Variables and functions */
 int SPI_CS_HIGH ; 
 int /*<<< orphan*/  gpio_direction_output (int /*<<< orphan*/ ,int) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_default_chip_info ; 
 struct mtk_spi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_spi_setup(struct spi_device *spi)
{
	struct mtk_spi *mdata = spi_master_get_devdata(spi->master);

	if (!spi->controller_data)
		spi->controller_data = (void *)&mtk_default_chip_info;

	if (mdata->dev_comp->need_pad_sel && gpio_is_valid(spi->cs_gpio))
		gpio_direction_output(spi->cs_gpio, !(spi->mode & SPI_CS_HIGH));

	return 0;
}