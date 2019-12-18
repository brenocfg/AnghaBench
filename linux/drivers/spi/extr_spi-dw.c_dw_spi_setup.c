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
struct spi_device {struct dw_spi_chip* controller_data; } ;
struct dw_spi_chip {int /*<<< orphan*/  type; int /*<<< orphan*/  poll_mode; scalar_t__ cs_control; } ;
struct chip_data {int /*<<< orphan*/  tmode; int /*<<< orphan*/  type; int /*<<< orphan*/  poll_mode; scalar_t__ cs_control; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SPI_TMOD_TR ; 
 struct chip_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct chip_data* spi_get_ctldata (struct spi_device*) ; 
 int /*<<< orphan*/  spi_set_ctldata (struct spi_device*,struct chip_data*) ; 

__attribute__((used)) static int dw_spi_setup(struct spi_device *spi)
{
	struct dw_spi_chip *chip_info = NULL;
	struct chip_data *chip;

	/* Only alloc on first setup */
	chip = spi_get_ctldata(spi);
	if (!chip) {
		chip = kzalloc(sizeof(struct chip_data), GFP_KERNEL);
		if (!chip)
			return -ENOMEM;
		spi_set_ctldata(spi, chip);
	}

	/*
	 * Protocol drivers may change the chip settings, so...
	 * if chip_info exists, use it
	 */
	chip_info = spi->controller_data;

	/* chip_info doesn't always exist */
	if (chip_info) {
		if (chip_info->cs_control)
			chip->cs_control = chip_info->cs_control;

		chip->poll_mode = chip_info->poll_mode;
		chip->type = chip_info->type;
	}

	chip->tmode = SPI_TMOD_TR;

	return 0;
}