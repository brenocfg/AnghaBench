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
 int EIO ; 
 int /*<<< orphan*/  I2C_M_RD ; 
 int debug ; 
 int /*<<< orphan*/  dprintk (int,char*) ; 
 int drxk_i2c_transfer (struct drxk_state*,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  pr_cont (char*,...) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i2c_read(struct drxk_state *state,
		    u8 adr, u8 *msg, int len, u8 *answ, int alen)
{
	int status;
	struct i2c_msg msgs[2] = {
		{.addr = adr, .flags = 0,
				    .buf = msg, .len = len},
		{.addr = adr, .flags = I2C_M_RD,
		 .buf = answ, .len = alen}
	};

	status = drxk_i2c_transfer(state, msgs, 2);
	if (status != 2) {
		if (debug > 2)
			pr_cont(": ERROR!\n");
		if (status >= 0)
			status = -EIO;

		pr_err("i2c read error at addr 0x%02x\n", adr);
		return status;
	}
	if (debug > 2) {
		int i;
		dprintk(2, ": read from");
		for (i = 0; i < len; i++)
			pr_cont(" %02x", msg[i]);
		pr_cont(", value = ");
		for (i = 0; i < alen; i++)
			pr_cont(" %02x", answ[i]);
		pr_cont("\n");
	}
	return 0;
}