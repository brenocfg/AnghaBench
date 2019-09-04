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
struct i2c_msg {int addr; int* buf; int len; int /*<<< orphan*/  flags; } ;
struct dm1105_dev {TYPE_1__* pdev; int /*<<< orphan*/  i2c_adap; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_M_RD ; 
 int IIC_24C01_addr ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int*) ; 
 int /*<<< orphan*/  dm1105_i2c_xfer (int /*<<< orphan*/ *,struct i2c_msg*,int) ; 

__attribute__((used)) static void dm1105_read_mac(struct dm1105_dev *dev, u8 *mac)
{
	static u8 command[1] = { 0x28 };

	struct i2c_msg msg[] = {
		{
			.addr = IIC_24C01_addr >> 1,
			.flags = 0,
			.buf = command,
			.len = 1
		}, {
			.addr = IIC_24C01_addr >> 1,
			.flags = I2C_M_RD,
			.buf = mac,
			.len = 6
		},
	};

	dm1105_i2c_xfer(&dev->i2c_adap, msg , 2);
	dev_info(&dev->pdev->dev, "MAC %pM\n", mac);
}