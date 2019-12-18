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
typedef  int u16 ;
struct s5k6aa {int /*<<< orphan*/  sd; } ;
struct i2c_client {int dummy; } ;
typedef  enum v4l2_mbus_type { ____Placeholder_v4l2_mbus_type } v4l2_mbus_type ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  REG_OIF_CFG_CHG ; 
 int /*<<< orphan*/  REG_OIF_EN_MIPI_LANES ; 
 int V4L2_MBUS_CSI2_DPHY ; 
 int V4L2_MBUS_PARALLEL ; 
 int s5k6aa_write (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int s5k6aa_configure_video_bus(struct s5k6aa *s5k6aa,
				      enum v4l2_mbus_type bus_type, int nlanes)
{
	struct i2c_client *client = v4l2_get_subdevdata(&s5k6aa->sd);
	u16 cfg = 0;
	int ret;

	/*
	 * TODO: The sensor is supposed to support BT.601 and BT.656
	 * but there is nothing indicating how to switch between both
	 * in the datasheet. For now default BT.601 interface is assumed.
	 */
	if (bus_type == V4L2_MBUS_CSI2_DPHY)
		cfg = nlanes;
	else if (bus_type != V4L2_MBUS_PARALLEL)
		return -EINVAL;

	ret = s5k6aa_write(client, REG_OIF_EN_MIPI_LANES, cfg);
	if (ret)
		return ret;
	return s5k6aa_write(client, REG_OIF_CFG_CHG, 1);
}