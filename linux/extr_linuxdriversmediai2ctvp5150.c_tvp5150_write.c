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
struct v4l2_subdev {int /*<<< orphan*/  dev; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  dev_dbg_lvl (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,unsigned char,unsigned char) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int tvp5150_write(struct v4l2_subdev *sd, unsigned char addr,
				 unsigned char value)
{
	struct i2c_client *c = v4l2_get_subdevdata(sd);
	int rc;

	dev_dbg_lvl(sd->dev, 2, debug, "tvp5150: writing %02x %02x\n", addr, value);
	rc = i2c_smbus_write_byte_data(c, addr, value);
	if (rc < 0)
		dev_err(sd->dev, "i2c i/o error: rc == %d\n", rc);

	return rc;
}