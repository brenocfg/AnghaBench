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
struct iio_dev {int dummy; } ;
struct atlas_data {TYPE_1__* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int atlas_set_interrupt (struct atlas_data*,int) ; 
 struct atlas_data* iio_priv (struct iio_dev*) ; 
 int iio_triggered_buffer_postenable (struct iio_dev*) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int atlas_buffer_postenable(struct iio_dev *indio_dev)
{
	struct atlas_data *data = iio_priv(indio_dev);
	int ret;

	ret = iio_triggered_buffer_postenable(indio_dev);
	if (ret)
		return ret;

	ret = pm_runtime_get_sync(&data->client->dev);
	if (ret < 0) {
		pm_runtime_put_noidle(&data->client->dev);
		return ret;
	}

	return atlas_set_interrupt(data, true);
}