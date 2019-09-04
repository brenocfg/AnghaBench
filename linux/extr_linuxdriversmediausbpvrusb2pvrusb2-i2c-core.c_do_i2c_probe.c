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
struct pvr2_hdw {int /*<<< orphan*/  i2c_adap; } ;
struct i2c_msg {int addr; int /*<<< orphan*/ * buf; scalar_t__ len; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct i2c_msg*) ; 
 int /*<<< orphan*/  I2C_M_RD ; 
 int i2c_transfer (int /*<<< orphan*/ *,struct i2c_msg*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_i2c_probe(struct pvr2_hdw *hdw, int addr)
{
	struct i2c_msg msg[1];
	int rc;
	msg[0].addr = 0;
	msg[0].flags = I2C_M_RD;
	msg[0].len = 0;
	msg[0].buf = NULL;
	msg[0].addr = addr;
	rc = i2c_transfer(&hdw->i2c_adap, msg, ARRAY_SIZE(msg));
	return rc == 1;
}