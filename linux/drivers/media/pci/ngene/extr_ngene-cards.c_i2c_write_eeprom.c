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
typedef  int /*<<< orphan*/  m ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int i2c_transfer (struct i2c_adapter*,struct i2c_msg*,int) ; 

__attribute__((used)) static int i2c_write_eeprom(struct i2c_adapter *adapter,
			    u8 adr, u16 reg, u8 data)
{
	struct device *pdev = adapter->dev.parent;
	u8 m[3] = {(reg >> 8), (reg & 0xff), data};
	struct i2c_msg msg = {.addr = adr, .flags = 0, .buf = m,
			      .len = sizeof(m)};

	if (i2c_transfer(adapter, &msg, 1) != 1) {
		dev_err(pdev, "Error writing EEPROM!\n");
		return -EIO;
	}
	return 0;
}