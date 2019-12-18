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
struct iio_dev {int /*<<< orphan*/  dev; } ;
struct hid_sensor_hub_device {int dummy; } ;
struct dev_rot_state {int /*<<< orphan*/  sampled_vals; } ;

/* Variables and functions */
 unsigned int HID_USAGE_SENSOR_ORIENT_QUATERNION ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,size_t,int) ; 
 struct dev_rot_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 struct iio_dev* platform_get_drvdata (void*) ; 

__attribute__((used)) static int dev_rot_capture_sample(struct hid_sensor_hub_device *hsdev,
				unsigned usage_id,
				size_t raw_len, char *raw_data,
				void *priv)
{
	struct iio_dev *indio_dev = platform_get_drvdata(priv);
	struct dev_rot_state *rot_state = iio_priv(indio_dev);

	if (usage_id == HID_USAGE_SENSOR_ORIENT_QUATERNION) {
		memcpy(rot_state->sampled_vals, raw_data,
					sizeof(rot_state->sampled_vals));
		dev_dbg(&indio_dev->dev, "Recd Quat len:%zu::%zu\n", raw_len,
					sizeof(rot_state->sampled_vals));
	}

	return 0;
}