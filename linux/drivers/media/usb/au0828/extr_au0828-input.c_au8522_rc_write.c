#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct i2c_msg {char* buf; int len; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct au0828_rc {TYPE_2__* dev; int /*<<< orphan*/  i2c_dev_addr; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_3__ {int /*<<< orphan*/  adapter; } ;
struct TYPE_4__ {TYPE_1__ i2c_client; } ;

/* Variables and functions */
 int EIO ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 

__attribute__((used)) static int au8522_rc_write(struct au0828_rc *ir, u16 reg, u8 data)
{
	int rc;
	char buf[] = { (reg >> 8) | 0x80, reg & 0xff, data };
	struct i2c_msg msg = { .addr = ir->i2c_dev_addr, .flags = 0,
			       .buf = buf, .len = sizeof(buf) };

	rc = i2c_transfer(ir->dev->i2c_client.adapter, &msg, 1);

	if (rc < 0)
		return rc;

	return (rc == 1) ? 0 : -EIO;
}