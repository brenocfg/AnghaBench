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
typedef  int u8 ;
struct i2c_msg {int addr; int* buf; int len; int /*<<< orphan*/  flags; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_M_RD ; 
 int i2c_transfer (struct i2c_adapter*,struct i2c_msg*,int) ; 

int ngene_port_has_cxd2099(struct i2c_adapter *i2c, u8 *type)
{
	u8 val;
	u8 probe[4] = { 0xe0, 0x00, 0x00, 0x00 }, data[4];
	struct i2c_msg msgs[2] = {{ .addr = 0x40,  .flags = 0,
				    .buf  = probe, .len   = 4 },
				  { .addr = 0x40,  .flags = I2C_M_RD,
				    .buf  = data,  .len   = 4 } };
	val = i2c_transfer(i2c, msgs, 2);
	if (val != 2)
		return 0;

	if (data[0] == 0x02 && data[1] == 0x2b && data[3] == 0x43)
		*type = 2;
	else
		*type = 1;
	return 1;
}