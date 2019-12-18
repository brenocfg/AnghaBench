#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct st_sensor_data {TYPE_1__* sensor_settings; int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;
struct iio_dev {int /*<<< orphan*/  active_scan_mask; } ;
struct TYPE_6__ {int mask; int /*<<< orphan*/  addr; } ;
struct TYPE_5__ {TYPE_3__ stat_drdy; } ;
struct TYPE_4__ {TYPE_2__ drdy_irq; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int st_sensors_new_samples_available(struct iio_dev *indio_dev,
					    struct st_sensor_data *sdata)
{
	int ret, status;

	/* How would I know if I can't check it? */
	if (!sdata->sensor_settings->drdy_irq.stat_drdy.addr)
		return -EINVAL;

	/* No scan mask, no interrupt */
	if (!indio_dev->active_scan_mask)
		return 0;

	ret = regmap_read(sdata->regmap,
			  sdata->sensor_settings->drdy_irq.stat_drdy.addr,
			  &status);
	if (ret < 0) {
		dev_err(sdata->dev,
			"error checking samples available\n");
		return ret;
	}

	if (status & sdata->sensor_settings->drdy_irq.stat_drdy.mask)
		return 1;

	return 0;
}