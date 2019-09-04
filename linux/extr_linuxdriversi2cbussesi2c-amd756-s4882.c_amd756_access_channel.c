#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
union i2c_smbus_data {scalar_t__ byte; } ;
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct i2c_adapter {int dummy; } ;
typedef  int s32 ;
struct TYPE_4__ {TYPE_1__* algo; } ;
struct TYPE_3__ {int (* smbus_xfer ) (struct i2c_adapter*,int,unsigned short,char,int,int,union i2c_smbus_data*) ;} ;

/* Variables and functions */
 int ENXIO ; 
 int I2C_SMBUS_BYTE_DATA ; 
 char I2C_SMBUS_WRITE ; 
 int /*<<< orphan*/  amd756_lock ; 
 TYPE_2__ amd756_smbus ; 
 scalar_t__ last_channels ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct i2c_adapter*,int,unsigned short,char,int,int,union i2c_smbus_data*) ; 
 int stub2 (struct i2c_adapter*,int,unsigned short,char,scalar_t__,int,union i2c_smbus_data*) ; 

__attribute__((used)) static inline s32 amd756_access_channel(struct i2c_adapter * adap, u16 addr,
					unsigned short flags, char read_write,
					u8 command, int size,
					union i2c_smbus_data * data,
					u8 channels)
{
	int error;

	/* We exclude the non-multiplexed addresses */
	if (addr != 0x4c && (addr & 0xfc) != 0x50 && (addr & 0xfc) != 0x30)
		return -ENXIO;

	mutex_lock(&amd756_lock);

	if (last_channels != channels) {
		union i2c_smbus_data mplxdata;
		mplxdata.byte = channels;

		error = amd756_smbus.algo->smbus_xfer(adap, 0x18, 0,
						      I2C_SMBUS_WRITE, 0x01,
						      I2C_SMBUS_BYTE_DATA,
						      &mplxdata);
		if (error)
			goto UNLOCK;
		last_channels = channels;
	}
	error = amd756_smbus.algo->smbus_xfer(adap, addr, flags, read_write,
					      command, size, data);

UNLOCK:
	mutex_unlock(&amd756_lock);
	return error;
}