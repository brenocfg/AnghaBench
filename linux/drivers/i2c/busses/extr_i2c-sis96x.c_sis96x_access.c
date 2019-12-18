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
union i2c_smbus_data {int byte; int word; } ;
typedef  int u8 ;
typedef  int u16 ;
struct i2c_adapter {int /*<<< orphan*/  dev; } ;
typedef  int s32 ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  I2C_SMBUS_BYTE 136 
#define  I2C_SMBUS_BYTE_DATA 135 
#define  I2C_SMBUS_PROC_CALL 134 
#define  I2C_SMBUS_QUICK 133 
#define  I2C_SMBUS_WORD_DATA 132 
 char I2C_SMBUS_WRITE ; 
#define  SIS96x_BYTE 131 
#define  SIS96x_BYTE_DATA 130 
#define  SIS96x_PROC_CALL 129 
 int SIS96x_QUICK ; 
#define  SIS96x_WORD_DATA 128 
 int /*<<< orphan*/  SMB_ADDR ; 
 int /*<<< orphan*/  SMB_BYTE ; 
 int /*<<< orphan*/  SMB_CMD ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int sis96x_read (int /*<<< orphan*/ ) ; 
 int sis96x_transaction (int) ; 
 int /*<<< orphan*/  sis96x_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static s32 sis96x_access(struct i2c_adapter * adap, u16 addr,
			 unsigned short flags, char read_write,
			 u8 command, int size, union i2c_smbus_data * data)
{
	int status;

	switch (size) {
	case I2C_SMBUS_QUICK:
		sis96x_write(SMB_ADDR, ((addr & 0x7f) << 1) | (read_write & 0x01));
		size = SIS96x_QUICK;
		break;

	case I2C_SMBUS_BYTE:
		sis96x_write(SMB_ADDR, ((addr & 0x7f) << 1) | (read_write & 0x01));
		if (read_write == I2C_SMBUS_WRITE)
			sis96x_write(SMB_CMD, command);
		size = SIS96x_BYTE;
		break;

	case I2C_SMBUS_BYTE_DATA:
		sis96x_write(SMB_ADDR, ((addr & 0x7f) << 1) | (read_write & 0x01));
		sis96x_write(SMB_CMD, command);
		if (read_write == I2C_SMBUS_WRITE)
			sis96x_write(SMB_BYTE, data->byte);
		size = SIS96x_BYTE_DATA;
		break;

	case I2C_SMBUS_PROC_CALL:
	case I2C_SMBUS_WORD_DATA:
		sis96x_write(SMB_ADDR, ((addr & 0x7f) << 1) | (read_write & 0x01));
		sis96x_write(SMB_CMD, command);
		if (read_write == I2C_SMBUS_WRITE) {
			sis96x_write(SMB_BYTE, data->word & 0xff);
			sis96x_write(SMB_BYTE + 1, (data->word & 0xff00) >> 8);
		}
		size = (size == I2C_SMBUS_PROC_CALL ? 
			SIS96x_PROC_CALL : SIS96x_WORD_DATA);
		break;

	default:
		dev_warn(&adap->dev, "Unsupported transaction %d\n", size);
		return -EOPNOTSUPP;
	}

	status = sis96x_transaction(size);
	if (status)
		return status;

	if ((size != SIS96x_PROC_CALL) &&
		((read_write == I2C_SMBUS_WRITE) || (size == SIS96x_QUICK)))
		return 0;

	switch (size) {
	case SIS96x_BYTE:
	case SIS96x_BYTE_DATA:
		data->byte = sis96x_read(SMB_BYTE);
		break;

	case SIS96x_WORD_DATA:
	case SIS96x_PROC_CALL:
		data->word = sis96x_read(SMB_BYTE) +
				(sis96x_read(SMB_BYTE + 1) << 8);
		break;
	}
	return 0;
}