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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct i2c_msg {int len; int /*<<< orphan*/ * buf; scalar_t__ flags; int /*<<< orphan*/  addr; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; int /*<<< orphan*/  addr; } ;
struct ad5820_device {int /*<<< orphan*/  subdev; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ad5820_write(struct ad5820_device *coil, u16 data)
{
	struct i2c_client *client = v4l2_get_subdevdata(&coil->subdev);
	struct i2c_msg msg;
	__be16 be_data;
	int r;

	if (!client->adapter)
		return -ENODEV;

	be_data = cpu_to_be16(data);
	msg.addr  = client->addr;
	msg.flags = 0;
	msg.len   = 2;
	msg.buf   = (u8 *)&be_data;

	r = i2c_transfer(client->adapter, &msg, 1);
	if (r < 0) {
		dev_err(&client->dev, "write failed, error %d\n", r);
		return r;
	}

	return 0;
}