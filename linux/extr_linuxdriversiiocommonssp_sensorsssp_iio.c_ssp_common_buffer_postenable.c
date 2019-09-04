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
struct ssp_sensor_data {int /*<<< orphan*/  type; int /*<<< orphan*/  buffer; } ;
struct ssp_data {int dummy; } ;
struct TYPE_4__ {TYPE_1__* parent; } ;
struct iio_dev {int /*<<< orphan*/  scan_bytes; TYPE_2__ dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 struct ssp_data* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct ssp_sensor_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  kmalloc (int /*<<< orphan*/ ,int) ; 
 int ssp_enable_sensor (struct ssp_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssp_get_sensor_delay (struct ssp_data*,int /*<<< orphan*/ ) ; 

int ssp_common_buffer_postenable(struct iio_dev *indio_dev)
{
	struct ssp_sensor_data *spd = iio_priv(indio_dev);
	struct ssp_data *data = dev_get_drvdata(indio_dev->dev.parent->parent);

	/* the allocation is made in post because scan size is known in this
	 * moment
	 * */
	spd->buffer = kmalloc(indio_dev->scan_bytes, GFP_KERNEL | GFP_DMA);
	if (!spd->buffer)
		return -ENOMEM;

	return ssp_enable_sensor(data, spd->type,
				 ssp_get_sensor_delay(data, spd->type));
}