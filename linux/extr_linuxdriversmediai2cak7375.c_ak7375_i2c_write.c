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
typedef  int u16 ;
struct i2c_client {int dummy; } ;
struct ak7375_device {int /*<<< orphan*/  sd; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int i2c_master_send (struct i2c_client*,char const*,int) ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ak7375_i2c_write(struct ak7375_device *ak7375,
	u8 addr, u16 data, u8 size)
{
	struct i2c_client *client = v4l2_get_subdevdata(&ak7375->sd);
	u8 buf[3];
	int ret;

	if (size != 1 && size != 2)
		return -EINVAL;
	buf[0] = addr;
	buf[size] = data & 0xff;
	if (size == 2)
		buf[1] = (data >> 8) & 0xff;
	ret = i2c_master_send(client, (const char *)buf, size + 1);
	if (ret < 0)
		return ret;
	if (ret != size + 1)
		return -EIO;

	return 0;
}