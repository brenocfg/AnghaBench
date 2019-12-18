#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct stm32_adc {unsigned int res; TYPE_2__* cfg; } ;
struct TYPE_7__ {struct device_node* of_node; } ;
struct iio_dev {TYPE_3__ dev; } ;
struct device_node {int dummy; } ;
struct TYPE_6__ {TYPE_1__* adc_info; } ;
struct TYPE_5__ {scalar_t__* resolutions; unsigned int num_res; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (TYPE_3__*,char*,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,scalar_t__) ; 
 struct stm32_adc* iio_priv (struct iio_dev*) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,scalar_t__*) ; 

__attribute__((used)) static int stm32_adc_of_get_resolution(struct iio_dev *indio_dev)
{
	struct device_node *node = indio_dev->dev.of_node;
	struct stm32_adc *adc = iio_priv(indio_dev);
	unsigned int i;
	u32 res;

	if (of_property_read_u32(node, "assigned-resolution-bits", &res))
		res = adc->cfg->adc_info->resolutions[0];

	for (i = 0; i < adc->cfg->adc_info->num_res; i++)
		if (res == adc->cfg->adc_info->resolutions[i])
			break;
	if (i >= adc->cfg->adc_info->num_res) {
		dev_err(&indio_dev->dev, "Bad resolution: %u bits\n", res);
		return -EINVAL;
	}

	dev_dbg(&indio_dev->dev, "Using %u bits resolution\n", res);
	adc->res = i;

	return 0;
}