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
struct i2c_msg {int flags; int addr; } ;
struct brcmstb_i2c_dev {int dummy; } ;

/* Variables and functions */
 int COND_NOSTOP ; 
 int COND_RESTART ; 
 int EREMOTEIO ; 
 int I2C_M_RD ; 
 int I2C_M_TEN ; 
 scalar_t__ brcmstb_i2c_write_data_byte (struct brcmstb_i2c_dev*,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmstb_set_i2c_start_stop (struct brcmstb_i2c_dev*,int) ; 
 int /*<<< orphan*/  bsc_writel (struct brcmstb_i2c_dev*,unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chip_address ; 
 unsigned char i2c_8bit_addr_from_msg (struct i2c_msg*) ; 

__attribute__((used)) static int brcmstb_i2c_do_addr(struct brcmstb_i2c_dev *dev,
			       struct i2c_msg *msg)
{
	unsigned char addr;

	if (msg->flags & I2C_M_TEN) {
		/* First byte is 11110XX0 where XX is upper 2 bits */
		addr = 0xF0 | ((msg->addr & 0x300) >> 7);
		bsc_writel(dev, addr, chip_address);

		/* Second byte is the remaining 8 bits */
		addr = msg->addr & 0xFF;
		if (brcmstb_i2c_write_data_byte(dev, &addr, 0) < 0)
			return -EREMOTEIO;

		if (msg->flags & I2C_M_RD) {
			/* For read, send restart without stop condition */
			brcmstb_set_i2c_start_stop(dev, COND_RESTART
						   | COND_NOSTOP);
			/* Then re-send the first byte with the read bit set */
			addr = 0xF0 | ((msg->addr & 0x300) >> 7) | 0x01;
			if (brcmstb_i2c_write_data_byte(dev, &addr, 0) < 0)
				return -EREMOTEIO;

		}
	} else {
		addr = i2c_8bit_addr_from_msg(msg);

		bsc_writel(dev, addr, chip_address);
	}

	return 0;
}