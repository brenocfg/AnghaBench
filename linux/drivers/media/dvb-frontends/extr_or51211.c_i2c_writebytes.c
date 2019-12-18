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
struct or51211_state {int /*<<< orphan*/  i2c; } ;
struct i2c_msg {int len; int /*<<< orphan*/ * buf; scalar_t__ flags; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int i2c_writebytes (struct or51211_state* state, u8 reg, const u8 *buf,
			   int len)
{
	int err;
	struct i2c_msg msg;
	msg.addr	= reg;
	msg.flags	= 0;
	msg.len		= len;
	msg.buf		= (u8 *)buf;

	if ((err = i2c_transfer (state->i2c, &msg, 1)) != 1) {
		pr_warn("error (addr %02x, err == %i)\n", reg, err);
		return -EREMOTEIO;
	}

	return 0;
}