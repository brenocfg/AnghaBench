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
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int AHB_MSB_ADDR_PTR ; 
 int GEN_REG_OFFSH ; 
 int s5k4ecgx_i2c_write (struct i2c_client*,int,int) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int s5k4ecgx_set_ahb_address(struct v4l2_subdev *sd)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	int ret;

	/* Set APB peripherals start address */
	ret = s5k4ecgx_i2c_write(client, AHB_MSB_ADDR_PTR, GEN_REG_OFFSH);
	if (ret < 0)
		return ret;
	/*
	 * FIXME: This is copied from s5k6aa, because of no information
	 * in s5k4ecgx's datasheet.
	 * sw_reset is activated to put device into idle status
	 */
	ret = s5k4ecgx_i2c_write(client, 0x0010, 0x0001);
	if (ret < 0)
		return ret;

	ret = s5k4ecgx_i2c_write(client, 0x1030, 0x0000);
	if (ret < 0)
		return ret;
	/* Halt ARM CPU */
	return s5k4ecgx_i2c_write(client, 0x0014, 0x0001);
}