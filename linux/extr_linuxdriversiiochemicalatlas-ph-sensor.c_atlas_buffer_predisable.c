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
 int iio_triggered_buffer_predisable (struct iio_dev*) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ *) ; 
 int pm_runtime_put_autosuspend (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int atlas_buffer_predisable(struct iio_dev *indio_dev)
{
	struct atlas_data *data = iio_priv(indio_dev);
	int ret;

	ret = iio_triggered_buffer_predisable(indio_dev);
	if (ret)
		return ret;

	ret = atlas_set_interrupt(data, false);
	if (ret)
		return ret;

	pm_runtime_mark_last_busy(&data->client->dev);
	return pm_runtime_put_autosuspend(&data->client->dev);
}