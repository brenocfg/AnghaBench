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
typedef  int /*<<< orphan*/  u8 ;
struct spi_device {int /*<<< orphan*/  dev; } ;
struct ad7816_chip_info {int /*<<< orphan*/  rdwr_pin; struct spi_device* spi_dev; } ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 int spi_write (struct spi_device*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ad7816_spi_write(struct ad7816_chip_info *chip, u8 data)
{
	struct spi_device *spi_dev = chip->spi_dev;
	int ret;

	gpiod_set_value(chip->rdwr_pin, 1);
	gpiod_set_value(chip->rdwr_pin, 0);
	ret = spi_write(spi_dev, &data, sizeof(data));
	if (ret < 0)
		dev_err(&spi_dev->dev, "SPI oti data write error\n");

	return ret;
}