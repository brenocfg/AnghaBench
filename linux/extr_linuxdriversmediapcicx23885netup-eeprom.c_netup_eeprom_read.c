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
typedef  unsigned char u8 ;
struct i2c_msg {unsigned char* buf; int len; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEPROM_I2C_ADDR ; 
 int /*<<< orphan*/  I2C_M_RD ; 
 int i2c_transfer (struct i2c_adapter*,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

int netup_eeprom_read(struct i2c_adapter *i2c_adap, u8 addr)
{
	int ret;
	unsigned char buf[2];

	/* Read from EEPROM */
	struct i2c_msg msg[] = {
		{
			.addr	= EEPROM_I2C_ADDR,
			.flags	= 0,
			.buf	= &buf[0],
			.len	= 1
		}, {
			.addr	= EEPROM_I2C_ADDR,
			.flags	= I2C_M_RD,
			.buf	= &buf[1],
			.len	= 1
		}

	};

	buf[0] = addr;
	buf[1] = 0x0;

	ret = i2c_transfer(i2c_adap, msg, 2);

	if (ret != 2) {
		pr_err("eeprom i2c read error, status=%d\n", ret);
		return -1;
	}

	return buf[1];
}