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
typedef  int /*<<< orphan*/  u16 ;
struct spi_device {int /*<<< orphan*/  dev; } ;
struct ad7816_chip_info {scalar_t__ mode; scalar_t__ id; int /*<<< orphan*/  rdwr_pin; int /*<<< orphan*/  busy_pin; int /*<<< orphan*/  convert_pin; int /*<<< orphan*/  channel_id; struct spi_device* spi_dev; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 scalar_t__ AD7816_PD ; 
 scalar_t__ ID_AD7816 ; 
 scalar_t__ ID_AD7817 ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ gpiod_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 int spi_read (struct spi_device*,int /*<<< orphan*/ *,int) ; 
 int spi_write (struct spi_device*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ad7816_spi_read(struct ad7816_chip_info *chip, u16 *data)
{
	struct spi_device *spi_dev = chip->spi_dev;
	int ret;
	__be16 buf;

	gpiod_set_value(chip->rdwr_pin, 1);
	gpiod_set_value(chip->rdwr_pin, 0);
	ret = spi_write(spi_dev, &chip->channel_id, sizeof(chip->channel_id));
	if (ret < 0) {
		dev_err(&spi_dev->dev, "SPI channel setting error\n");
		return ret;
	}
	gpiod_set_value(chip->rdwr_pin, 1);

	if (chip->mode == AD7816_PD) { /* operating mode 2 */
		gpiod_set_value(chip->convert_pin, 1);
		gpiod_set_value(chip->convert_pin, 0);
	} else { /* operating mode 1 */
		gpiod_set_value(chip->convert_pin, 0);
		gpiod_set_value(chip->convert_pin, 1);
	}

	if (chip->id == ID_AD7816 || chip->id == ID_AD7817) {
		while (gpiod_get_value(chip->busy_pin))
			cpu_relax();
	}

	gpiod_set_value(chip->rdwr_pin, 0);
	gpiod_set_value(chip->rdwr_pin, 1);
	ret = spi_read(spi_dev, &buf, sizeof(*data));
	if (ret < 0) {
		dev_err(&spi_dev->dev, "SPI data read error\n");
		return ret;
	}

	*data = be16_to_cpu(buf);

	return ret;
}