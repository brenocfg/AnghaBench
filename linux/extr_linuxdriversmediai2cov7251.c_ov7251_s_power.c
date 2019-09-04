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
struct v4l2_subdev {int dummy; } ;
struct ov7251 {int power_on; int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ov7251_global_init_setting ; 
 int /*<<< orphan*/  ov7251_set_power_off (struct ov7251*) ; 
 int ov7251_set_power_on (struct ov7251*) ; 
 int ov7251_set_register_array (struct ov7251*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ov7251* to_ov7251 (struct v4l2_subdev*) ; 

__attribute__((used)) static int ov7251_s_power(struct v4l2_subdev *sd, int on)
{
	struct ov7251 *ov7251 = to_ov7251(sd);
	int ret = 0;

	mutex_lock(&ov7251->lock);

	/* If the power state is not modified - no work to do. */
	if (ov7251->power_on == !!on)
		goto exit;

	if (on) {
		ret = ov7251_set_power_on(ov7251);
		if (ret < 0)
			goto exit;

		ret = ov7251_set_register_array(ov7251,
					ov7251_global_init_setting,
					ARRAY_SIZE(ov7251_global_init_setting));
		if (ret < 0) {
			dev_err(ov7251->dev, "could not set init registers\n");
			ov7251_set_power_off(ov7251);
			goto exit;
		}

		ov7251->power_on = true;
	} else {
		ov7251_set_power_off(ov7251);
		ov7251->power_on = false;
	}

exit:
	mutex_unlock(&ov7251->lock);

	return ret;
}