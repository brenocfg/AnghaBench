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
struct i2c_msg {int len; int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_8bit_addr_from_msg (struct i2c_msg*) ; 
 int /*<<< orphan*/  i2c_smbus_pec (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static u8 i2c_smbus_msg_pec(u8 pec, struct i2c_msg *msg)
{
	/* The address will be sent first */
	u8 addr = i2c_8bit_addr_from_msg(msg);
	pec = i2c_smbus_pec(pec, &addr, 1);

	/* The data buffer follows */
	return i2c_smbus_pec(pec, msg->buf, msg->len);
}