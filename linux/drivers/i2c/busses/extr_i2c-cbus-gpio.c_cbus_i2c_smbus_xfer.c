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
union i2c_smbus_data {int word; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct i2c_adapter {int dummy; } ;
struct cbus_host {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 char I2C_SMBUS_READ ; 
 int I2C_SMBUS_WORD_DATA ; 
 int cbus_transfer (struct cbus_host*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct cbus_host* i2c_get_adapdata (struct i2c_adapter*) ; 

__attribute__((used)) static int cbus_i2c_smbus_xfer(struct i2c_adapter	*adapter,
			       u16			addr,
			       unsigned short		flags,
			       char			read_write,
			       u8			command,
			       int			size,
			       union i2c_smbus_data	*data)
{
	struct cbus_host *chost = i2c_get_adapdata(adapter);
	int ret;

	if (size != I2C_SMBUS_WORD_DATA)
		return -EINVAL;

	ret = cbus_transfer(chost, read_write == I2C_SMBUS_READ, addr,
			    command, data->word);
	if (ret < 0)
		return ret;

	if (read_write == I2C_SMBUS_READ)
		data->word = ret;

	return 0;
}