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
struct spi_device {int max_speed_hz; int /*<<< orphan*/  dev; } ;
struct mt7621_spi {int sys_freq; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct mt7621_spi* spidev_to_mt7621_spi (struct spi_device*) ; 

__attribute__((used)) static int mt7621_spi_setup(struct spi_device *spi)
{
	struct mt7621_spi *rs = spidev_to_mt7621_spi(spi);

	if ((spi->max_speed_hz == 0) ||
	    (spi->max_speed_hz > (rs->sys_freq / 2)))
		spi->max_speed_hz = rs->sys_freq / 2;

	if (spi->max_speed_hz < (rs->sys_freq / 4097)) {
		dev_err(&spi->dev, "setup: requested speed is too low %d Hz\n",
			spi->max_speed_hz);
		return -EINVAL;
	}

	return 0;
}