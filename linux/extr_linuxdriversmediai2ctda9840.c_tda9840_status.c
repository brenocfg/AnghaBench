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
typedef  int u8 ;
struct v4l2_subdev {int dummy; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  debug ; 
 int i2c_master_recv (struct i2c_client*,int*,int) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,...) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int tda9840_status(struct v4l2_subdev *sd)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	int rc;
	u8 byte;

	rc = i2c_master_recv(client, &byte, 1);
	if (rc != 1) {
		v4l2_dbg(1, debug, sd,
			"i2c_master_recv() failed\n");
		if (rc < 0)
			return rc;
		return -EIO;
	}

	if (byte & 0x80) {
		v4l2_dbg(1, debug, sd,
			"TDA9840_DETECT: register contents invalid\n");
		return -EINVAL;
	}

	v4l2_dbg(1, debug, sd, "TDA9840_DETECT: byte: 0x%02x\n", byte);
	return byte & 0x60;
}