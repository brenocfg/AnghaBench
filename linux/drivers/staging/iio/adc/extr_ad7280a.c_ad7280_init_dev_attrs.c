#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  attr; } ;
struct iio_dev_attr {TYPE_2__ dev_attr; } ;
struct device {int dummy; } ;
struct ad7280_state {struct iio_dev_attr* iio_attr; TYPE_1__* spi; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int AD7280A_CB1_TIMER ; 
 int AD7280A_CELLS_PER_DEV ; 
 int AD7280A_CELL_VOLTAGE_1 ; 
 int AD7280A_CELL_VOLTAGE_6 ; 
 int /*<<< orphan*/ ** ad7280_attributes ; 
 int ad7280_balance_switch_attr_init (struct iio_dev_attr*,struct device*,int,int) ; 
 int ad7280_balance_timer_attr_init (struct iio_dev_attr*,struct device*,int,int) ; 
 int ad7280a_devaddr (int) ; 

__attribute__((used)) static int ad7280_init_dev_attrs(struct ad7280_state *st, int dev, int *cnt)
{
	int addr, ch, i, ret;
	struct iio_dev_attr *iio_attr;
	struct device *sdev = &st->spi->dev;

	for (ch = AD7280A_CELL_VOLTAGE_1; ch <= AD7280A_CELL_VOLTAGE_6; ch++) {
		iio_attr = &st->iio_attr[*cnt];
		addr = ad7280a_devaddr(dev) << 8 | ch;
		i = dev * AD7280A_CELLS_PER_DEV + ch;

		ret = ad7280_balance_switch_attr_init(iio_attr, sdev, addr, i);
		if (ret < 0)
			return ret;

		ad7280_attributes[*cnt] = &iio_attr->dev_attr.attr;

		(*cnt)++;
		iio_attr = &st->iio_attr[*cnt];
		addr = ad7280a_devaddr(dev) << 8 | (AD7280A_CB1_TIMER + ch);

		ret = ad7280_balance_timer_attr_init(iio_attr, sdev, addr, i);
		if (ret < 0)
			return ret;

		ad7280_attributes[*cnt] = &iio_attr->dev_attr.attr;
		(*cnt)++;
	}

	ad7280_attributes[*cnt] = NULL;

	return 0;
}