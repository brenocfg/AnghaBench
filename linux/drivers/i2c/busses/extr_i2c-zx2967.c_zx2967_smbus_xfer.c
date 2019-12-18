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
typedef  union i2c_smbus_data {int dummy; } i2c_smbus_data ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct zx2967_i2c {int dummy; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  I2C_SMBUS_BYTE 131 
#define  I2C_SMBUS_BYTE_DATA 130 
#define  I2C_SMBUS_QUICK 129 
 char I2C_SMBUS_READ ; 
#define  I2C_SMBUS_WORD_DATA 128 
 char I2C_SMBUS_WRITE ; 
 struct zx2967_i2c* i2c_get_adapdata (struct i2c_adapter*) ; 
 int /*<<< orphan*/  zx2967_smbus_xfer_prepare (struct zx2967_i2c*,int /*<<< orphan*/ ,char,int /*<<< orphan*/ ,int,union i2c_smbus_data*) ; 
 int zx2967_smbus_xfer_read (struct zx2967_i2c*,int,union i2c_smbus_data*) ; 
 int zx2967_smbus_xfer_write (struct zx2967_i2c*) ; 

__attribute__((used)) static int zx2967_smbus_xfer(struct i2c_adapter *adap, u16 addr,
			     unsigned short flags, char read_write,
			     u8 command, int size, union i2c_smbus_data *data)
{
	struct zx2967_i2c *i2c = i2c_get_adapdata(adap);

	if (size == I2C_SMBUS_QUICK)
		read_write = I2C_SMBUS_WRITE;

	switch (size) {
	case I2C_SMBUS_QUICK:
	case I2C_SMBUS_BYTE:
	case I2C_SMBUS_BYTE_DATA:
	case I2C_SMBUS_WORD_DATA:
		zx2967_smbus_xfer_prepare(i2c, addr, read_write,
					  command, size, data);
		break;
	default:
		return -EOPNOTSUPP;
	}

	if (read_write == I2C_SMBUS_READ)
		return zx2967_smbus_xfer_read(i2c, size, data);

	return zx2967_smbus_xfer_write(i2c);
}