#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct i2c_msg {int flags; int /*<<< orphan*/  len; int /*<<< orphan*/  addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  nr; } ;
struct bcm2835_i2c_dev {TYPE_1__ adapter; } ;

/* Variables and functions */
 int I2C_M_IGNORE_NAK ; 
 int I2C_M_NOSTART ; 
 int I2C_M_NO_RD_ACK ; 
 int I2C_M_RD ; 
 int I2C_M_RECV_LEN ; 
 int I2C_M_REV_DIR_ADDR ; 
 int I2C_M_STOP ; 
 int I2C_M_TEN ; 
 int /*<<< orphan*/  pr_info (char*,char const*,int,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char*,char*,char*,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcm2835_debug_print_msg(struct bcm2835_i2c_dev *i2c_dev,
				    struct i2c_msg *msg, int i, int total,
				    const char *fname)
{
	pr_info("%s: msg(%d/%d) %s addr=0x%02x, len=%u flags=%s%s%s%s%s%s%s [i2c%d]\n",
		fname, i, total,
		msg->flags & I2C_M_RD ? "read" : "write", msg->addr, msg->len,
		msg->flags & I2C_M_TEN ? "TEN" : "",
		msg->flags & I2C_M_RECV_LEN ? "RECV_LEN" : "",
		msg->flags & I2C_M_NO_RD_ACK ? "NO_RD_ACK" : "",
		msg->flags & I2C_M_IGNORE_NAK ? "IGNORE_NAK" : "",
		msg->flags & I2C_M_REV_DIR_ADDR ? "REV_DIR_ADDR" : "",
		msg->flags & I2C_M_NOSTART ? "NOSTART" : "",
		msg->flags & I2C_M_STOP ? "STOP" : "",
		i2c_dev->adapter.nr);
}