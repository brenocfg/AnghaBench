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
struct ina2xx_chip_info {int /*<<< orphan*/  regmap; TYPE_1__* config; } ;
struct iio_dev {int dummy; } ;
struct TYPE_2__ {scalar_t__ chip_id; } ;

/* Variables and functions */
 unsigned int INA219_CNVR ; 
 unsigned int INA226_CVRF ; 
 int /*<<< orphan*/  INA226_MASK_ENABLE ; 
 int /*<<< orphan*/  INA2XX_BUS_VOLTAGE ; 
 struct ina2xx_chip_info* iio_priv (struct iio_dev*) ; 
 scalar_t__ ina226 ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int ina2xx_conversion_ready(struct iio_dev *indio_dev)
{
	struct ina2xx_chip_info *chip = iio_priv(indio_dev);
	int ret;
	unsigned int alert;

	/*
	 * Because the timer thread and the chip conversion clock
	 * are asynchronous, the period difference will eventually
	 * result in reading V[k-1] again, or skip V[k] at time Tk.
	 * In order to resync the timer with the conversion process
	 * we check the ConVersionReadyFlag.
	 * On hardware that supports using the ALERT pin to toggle a
	 * GPIO a triggered buffer could be used instead.
	 * For now, we do an extra read of the MASK_ENABLE register (INA226)
	 * resp. the BUS_VOLTAGE register (INA219).
	 */
	if (chip->config->chip_id == ina226) {
		ret = regmap_read(chip->regmap,
				  INA226_MASK_ENABLE, &alert);
		alert &= INA226_CVRF;
	} else {
		ret = regmap_read(chip->regmap,
				  INA2XX_BUS_VOLTAGE, &alert);
		alert &= INA219_CNVR;
	}

	if (ret < 0)
		return ret;

	return !!alert;
}