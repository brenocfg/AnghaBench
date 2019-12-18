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
struct ov5645 {int power_count; int /*<<< orphan*/  power_lock; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OV5645_IO_MIPI_CTRL00 ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ov5645_global_init_setting ; 
 int /*<<< orphan*/  ov5645_set_power_off (struct ov5645*) ; 
 int ov5645_set_power_on (struct ov5645*) ; 
 int ov5645_set_register_array (struct ov5645*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ov5645_write_reg (struct ov5645*,int /*<<< orphan*/ ,int) ; 
 struct ov5645* to_ov5645 (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int ov5645_s_power(struct v4l2_subdev *sd, int on)
{
	struct ov5645 *ov5645 = to_ov5645(sd);
	int ret = 0;

	mutex_lock(&ov5645->power_lock);

	/* If the power count is modified from 0 to != 0 or from != 0 to 0,
	 * update the power state.
	 */
	if (ov5645->power_count == !on) {
		if (on) {
			ret = ov5645_set_power_on(ov5645);
			if (ret < 0)
				goto exit;

			ret = ov5645_set_register_array(ov5645,
					ov5645_global_init_setting,
					ARRAY_SIZE(ov5645_global_init_setting));
			if (ret < 0) {
				dev_err(ov5645->dev,
					"could not set init registers\n");
				ov5645_set_power_off(ov5645);
				goto exit;
			}

			usleep_range(500, 1000);
		} else {
			ov5645_write_reg(ov5645, OV5645_IO_MIPI_CTRL00, 0x58);
			ov5645_set_power_off(ov5645);
		}
	}

	/* Update the power count. */
	ov5645->power_count += on ? 1 : -1;
	WARN_ON(ov5645->power_count < 0);

exit:
	mutex_unlock(&ov5645->power_lock);

	return ret;
}