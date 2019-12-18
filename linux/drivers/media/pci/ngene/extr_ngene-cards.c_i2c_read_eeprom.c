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
typedef  int u8 ;
typedef  int u16 ;
struct i2c_msg {int addr; int* buf; int len; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {struct device* parent; } ;
struct i2c_adapter {TYPE_1__ dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  I2C_M_RD ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int i2c_transfer (struct i2c_adapter*,struct i2c_msg*,int) ; 

__attribute__((used)) static int i2c_read_eeprom(struct i2c_adapter *adapter,
			   u8 adr, u16 reg, u8 *data, int len)
{
	struct device *pdev = adapter->dev.parent;
	u8 msg[2] = {(reg >> 8), (reg & 0xff)};
	struct i2c_msg msgs[2] = {{.addr = adr, .flags = 0,
				   .buf = msg, .len = 2 },
				  {.addr = adr, .flags = I2C_M_RD,
				   .buf = data, .len = len} };

	if (i2c_transfer(adapter, msgs, 2) != 2) {
		dev_err(pdev, "Error reading EEPROM\n");
		return -EIO;
	}
	return 0;
}