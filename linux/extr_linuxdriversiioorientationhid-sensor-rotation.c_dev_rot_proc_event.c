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
typedef  int /*<<< orphan*/  u8 ;
struct iio_dev {int /*<<< orphan*/  dev; } ;
struct hid_sensor_hub_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  data_ready; } ;
struct dev_rot_state {scalar_t__ sampled_vals; TYPE_1__ common_attributes; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  hid_sensor_push_data (struct iio_dev*,int /*<<< orphan*/ *,int) ; 
 struct dev_rot_state* iio_priv (struct iio_dev*) ; 
 struct iio_dev* platform_get_drvdata (void*) ; 

__attribute__((used)) static int dev_rot_proc_event(struct hid_sensor_hub_device *hsdev,
				unsigned usage_id,
				void *priv)
{
	struct iio_dev *indio_dev = platform_get_drvdata(priv);
	struct dev_rot_state *rot_state = iio_priv(indio_dev);

	dev_dbg(&indio_dev->dev, "dev_rot_proc_event\n");
	if (atomic_read(&rot_state->common_attributes.data_ready))
		hid_sensor_push_data(indio_dev,
				(u8 *)rot_state->sampled_vals,
				sizeof(rot_state->sampled_vals));

	return 0;
}