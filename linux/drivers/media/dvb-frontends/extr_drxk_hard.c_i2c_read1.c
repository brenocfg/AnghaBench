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
struct i2c_msg {int len; int /*<<< orphan*/ * buf; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct drxk_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_M_RD ; 
 int drxk_i2c_transfer (struct drxk_state*,struct i2c_msg*,int) ; 

__attribute__((used)) static int i2c_read1(struct drxk_state *state, u8 adr, u8 *val)
{
	struct i2c_msg msgs[1] = { {.addr = adr, .flags = I2C_M_RD,
				    .buf = val, .len = 1}
	};

	return drxk_i2c_transfer(state, msgs, 1);
}