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
 int debug ; 
 int /*<<< orphan*/  dprintk (int,char*) ; 
 int drxk_i2c_transfer (struct drxk_state*,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  pr_cont (char*,...) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i2c_write(struct drxk_state *state, u8 adr, u8 *data, int len)
{
	int status;
	struct i2c_msg msg = {
	    .addr = adr, .flags = 0, .buf = data, .len = len };

	dprintk(3, ":");
	if (debug > 2) {
		int i;
		for (i = 0; i < len; i++)
			pr_cont(" %02x", data[i]);
		pr_cont("\n");
	}
	status = drxk_i2c_transfer(state, &msg, 1);
	if (status >= 0 && status != 1)
		status = -EIO;

	if (status < 0)
		pr_err("i2c write error at addr 0x%02x\n", adr);

	return status;
}