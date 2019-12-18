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
struct mii_bus {struct i2c_adapter* priv; } ;
struct i2c_msg {int addr; int len; int* buf; scalar_t__ flags; } ;
struct i2c_adapter {int dummy; } ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int ARRAY_SIZE (struct i2c_msg*) ; 
 scalar_t__ I2C_M_RD ; 
 int i2c_mii_phy_addr (int) ; 
 int /*<<< orphan*/  i2c_mii_valid_phy_id (int) ; 
 int i2c_transfer (struct i2c_adapter*,struct i2c_msg*,int) ; 

__attribute__((used)) static int i2c_mii_read(struct mii_bus *bus, int phy_id, int reg)
{
	struct i2c_adapter *i2c = bus->priv;
	struct i2c_msg msgs[2];
	u8 data[2], dev_addr = reg;
	int bus_addr, ret;

	if (!i2c_mii_valid_phy_id(phy_id))
		return 0xffff;

	bus_addr = i2c_mii_phy_addr(phy_id);
	msgs[0].addr = bus_addr;
	msgs[0].flags = 0;
	msgs[0].len = 1;
	msgs[0].buf = &dev_addr;
	msgs[1].addr = bus_addr;
	msgs[1].flags = I2C_M_RD;
	msgs[1].len = sizeof(data);
	msgs[1].buf = data;

	ret = i2c_transfer(i2c, msgs, ARRAY_SIZE(msgs));
	if (ret != ARRAY_SIZE(msgs))
		return 0xffff;

	return data[0] << 8 | data[1];
}