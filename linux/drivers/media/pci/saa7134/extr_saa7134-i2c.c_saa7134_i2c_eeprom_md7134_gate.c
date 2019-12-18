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
struct saa7134_dev {int /*<<< orphan*/  name; int /*<<< orphan*/  i2c_adap; } ;
struct i2c_msg {int addr; int* buf; int len; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_M_RD ; 
 int i2c_transfer (int /*<<< orphan*/ *,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void saa7134_i2c_eeprom_md7134_gate(struct saa7134_dev *dev)
{
	u8 subaddr = 0x7, dmdregval;
	u8 data[2];
	int ret;
	struct i2c_msg i2cgatemsg_r[] = { {.addr = 0x08, .flags = 0,
					   .buf = &subaddr, .len = 1},
					  {.addr = 0x08,
					   .flags = I2C_M_RD,
					   .buf = &dmdregval, .len = 1}
					};
	struct i2c_msg i2cgatemsg_w[] = { {.addr = 0x08, .flags = 0,
					   .buf = data, .len = 2} };

	ret = i2c_transfer(&dev->i2c_adap, i2cgatemsg_r, 2);
	if ((ret == 2) && (dmdregval & 0x2)) {
		pr_debug("%s: DVB-T demod i2c gate was left open\n",
			 dev->name);

		data[0] = subaddr;
		data[1] = (dmdregval & ~0x2);
		if (i2c_transfer(&dev->i2c_adap, i2cgatemsg_w, 1) != 1)
			pr_err("%s: EEPROM i2c gate close failure\n",
			       dev->name);
	}
}