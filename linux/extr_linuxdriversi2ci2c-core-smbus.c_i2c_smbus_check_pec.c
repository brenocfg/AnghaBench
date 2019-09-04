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
struct i2c_msg {size_t len; int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 int EBADMSG ; 
 int /*<<< orphan*/  i2c_smbus_msg_pec (int /*<<< orphan*/ ,struct i2c_msg*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i2c_smbus_check_pec(u8 cpec, struct i2c_msg *msg)
{
	u8 rpec = msg->buf[--msg->len];
	cpec = i2c_smbus_msg_pec(cpec, msg);

	if (rpec != cpec) {
		pr_debug("Bad PEC 0x%02x vs. 0x%02x\n",
			rpec, cpec);
		return -EBADMSG;
	}
	return 0;
}