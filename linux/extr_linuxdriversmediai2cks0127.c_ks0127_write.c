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
typedef  char u8 ;
struct v4l2_subdev {int dummy; } ;
struct ks0127 {char* regs; } ;
struct i2c_client {int dummy; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  debug ; 
 int i2c_master_send (struct i2c_client*,char*,int) ; 
 struct ks0127* to_ks0127 (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static void ks0127_write(struct v4l2_subdev *sd, u8 reg, u8 val)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct ks0127 *ks = to_ks0127(sd);
	char msg[] = { reg, val };

	if (i2c_master_send(client, msg, sizeof(msg)) != sizeof(msg))
		v4l2_dbg(1, debug, sd, "write error\n");

	ks->regs[reg] = val;
}