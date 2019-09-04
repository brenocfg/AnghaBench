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
typedef  size_t u8 ;
struct i2c_client {int dummy; } ;
struct bt866 {size_t* reg; int /*<<< orphan*/  sd; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug ; 
 int i2c_master_send (struct i2c_client*,size_t*,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  schedule_timeout_interruptible (int /*<<< orphan*/ ) ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l_dbg (int,int /*<<< orphan*/ ,struct i2c_client*,char*,size_t,size_t) ; 
 int /*<<< orphan*/  v4l_warn (struct i2c_client*,char*,...) ; 

__attribute__((used)) static int bt866_write(struct bt866 *encoder, u8 subaddr, u8 data)
{
	struct i2c_client *client = v4l2_get_subdevdata(&encoder->sd);
	u8 buffer[2];
	int err;

	buffer[0] = subaddr;
	buffer[1] = data;

	encoder->reg[subaddr] = data;

	v4l_dbg(1, debug, client, "write 0x%02x = 0x%02x\n", subaddr, data);

	for (err = 0; err < 3;) {
		if (i2c_master_send(client, buffer, 2) == 2)
			break;
		err++;
		v4l_warn(client, "error #%d writing to 0x%02x\n",
				err, subaddr);
		schedule_timeout_interruptible(msecs_to_jiffies(100));
	}
	if (err == 3) {
		v4l_warn(client, "giving up\n");
		return -1;
	}

	return 0;
}