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
struct lp8788_platform_data {struct iio_map* adc_pdata; } ;
struct lp8788_adc {struct iio_map* map; } ;
struct iio_map {int dummy; } ;
struct iio_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int iio_map_array_register (struct iio_dev*,struct iio_map*) ; 
 struct iio_map* lp8788_default_iio_maps ; 

__attribute__((used)) static int lp8788_iio_map_register(struct iio_dev *indio_dev,
				struct lp8788_platform_data *pdata,
				struct lp8788_adc *adc)
{
	struct iio_map *map;
	int ret;

	map = (!pdata || !pdata->adc_pdata) ?
		lp8788_default_iio_maps : pdata->adc_pdata;

	ret = iio_map_array_register(indio_dev, map);
	if (ret) {
		dev_err(&indio_dev->dev, "iio map err: %d\n", ret);
		return ret;
	}

	adc->map = map;
	return 0;
}