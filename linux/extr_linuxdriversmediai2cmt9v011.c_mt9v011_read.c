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
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug ; 
 int i2c_master_recv (struct i2c_client*,char*,int) ; 
 int i2c_master_send (struct i2c_client*,unsigned char*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,unsigned char,...) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int mt9v011_read(struct v4l2_subdev *sd, unsigned char addr)
{
	struct i2c_client *c = v4l2_get_subdevdata(sd);
	__be16 buffer;
	int rc, val;

	rc = i2c_master_send(c, &addr, 1);
	if (rc != 1)
		v4l2_dbg(0, debug, sd,
			 "i2c i/o error: rc == %d (should be 1)\n", rc);

	msleep(10);

	rc = i2c_master_recv(c, (char *)&buffer, 2);
	if (rc != 2)
		v4l2_dbg(0, debug, sd,
			 "i2c i/o error: rc == %d (should be 2)\n", rc);

	val = be16_to_cpu(buffer);

	v4l2_dbg(2, debug, sd, "mt9v011: read 0x%02x = 0x%04x\n", addr, val);

	return val;
}