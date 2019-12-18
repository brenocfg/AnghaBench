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
struct ms5611_state {int (* read_adc_temp_and_pressure ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;TYPE_1__* chip_info; } ;
struct iio_dev {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_2__ {int (* temp_and_pressure_compensate ) (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct ms5611_state* iio_priv (struct iio_dev*) ; 
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int stub2 (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ms5611_read_temp_and_pressure(struct iio_dev *indio_dev,
					 s32 *temp, s32 *pressure)
{
	int ret;
	struct ms5611_state *st = iio_priv(indio_dev);

	ret = st->read_adc_temp_and_pressure(&indio_dev->dev, temp, pressure);
	if (ret < 0) {
		dev_err(&indio_dev->dev,
			"failed to read temperature and pressure\n");
		return ret;
	}

	return st->chip_info->temp_and_pressure_compensate(st->chip_info,
							   temp, pressure);
}