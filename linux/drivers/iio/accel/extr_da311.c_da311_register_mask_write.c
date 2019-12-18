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
typedef  int u16 ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int DA311_REG_BANK ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int,int) ; 

__attribute__((used)) static int da311_register_mask_write(struct i2c_client *client, u16 addr,
				     u8 mask, u8 data)
{
	int ret;
	u8 tmp_data = 0;

	if (addr & 0xff00) {
		/* Select bank 1 */
		ret = i2c_smbus_write_byte_data(client, DA311_REG_BANK, 0x01);
		if (ret < 0)
			return ret;
	}

	if (mask != 0xff) {
		ret = i2c_smbus_read_byte_data(client, addr);
		if (ret < 0)
			return ret;
		tmp_data = ret;
	}

	tmp_data &= ~mask;
	tmp_data |= data & mask;
	ret = i2c_smbus_write_byte_data(client, addr & 0xff, tmp_data);
	if (ret < 0)
		return ret;

	if (addr & 0xff00) {
		/* Back to bank 0 */
		ret = i2c_smbus_write_byte_data(client, DA311_REG_BANK, 0x00);
		if (ret < 0)
			return ret;
	}

	return 0;
}