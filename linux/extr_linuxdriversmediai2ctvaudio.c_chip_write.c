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
struct v4l2_subdev {int dummy; } ;
struct i2c_client {int dummy; } ;
struct TYPE_2__ {int* bytes; } ;
struct CHIPSTATE {TYPE_1__ shadow; struct v4l2_subdev sd; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  debug ; 
 int i2c_master_send (struct i2c_client*,unsigned char*,int) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,int,...) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_info (struct v4l2_subdev*,char*,int) ; 
 int /*<<< orphan*/  v4l2_warn (struct v4l2_subdev*,char*,int,...) ; 

__attribute__((used)) static int chip_write(struct CHIPSTATE *chip, int subaddr, int val)
{
	struct v4l2_subdev *sd = &chip->sd;
	struct i2c_client *c = v4l2_get_subdevdata(sd);
	unsigned char buffer[2];
	int rc;

	if (subaddr < 0) {
		v4l2_dbg(1, debug, sd, "chip_write: 0x%x\n", val);
		chip->shadow.bytes[1] = val;
		buffer[0] = val;
		rc = i2c_master_send(c, buffer, 1);
		if (rc != 1) {
			v4l2_warn(sd, "I/O error (write 0x%x)\n", val);
			if (rc < 0)
				return rc;
			return -EIO;
		}
	} else {
		if (subaddr + 1 >= ARRAY_SIZE(chip->shadow.bytes)) {
			v4l2_info(sd,
				"Tried to access a non-existent register: %d\n",
				subaddr);
			return -EINVAL;
		}

		v4l2_dbg(1, debug, sd, "chip_write: reg%d=0x%x\n",
			subaddr, val);
		chip->shadow.bytes[subaddr+1] = val;
		buffer[0] = subaddr;
		buffer[1] = val;
		rc = i2c_master_send(c, buffer, 2);
		if (rc != 2) {
			v4l2_warn(sd, "I/O error (write reg%d=0x%x)\n",
				subaddr, val);
			if (rc < 0)
				return rc;
			return -EIO;
		}
	}
	return 0;
}