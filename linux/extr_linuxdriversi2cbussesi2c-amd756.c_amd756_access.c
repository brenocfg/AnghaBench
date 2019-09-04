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
union i2c_smbus_data {int byte; int word; int* block; } ;
typedef  int u8 ;
typedef  int u16 ;
struct i2c_adapter {int /*<<< orphan*/  dev; } ;
typedef  int s32 ;

/* Variables and functions */
#define  AMD756_BLOCK_DATA 136 
#define  AMD756_BYTE 135 
#define  AMD756_BYTE_DATA 134 
 int AMD756_QUICK ; 
#define  AMD756_WORD_DATA 133 
 int EOPNOTSUPP ; 
 int GE_CYC_TYPE_MASK ; 
#define  I2C_SMBUS_BLOCK_DATA 132 
#define  I2C_SMBUS_BYTE 131 
#define  I2C_SMBUS_BYTE_DATA 130 
#define  I2C_SMBUS_QUICK 129 
#define  I2C_SMBUS_WORD_DATA 128 
 char I2C_SMBUS_WRITE ; 
 int /*<<< orphan*/  SMB_GLOBAL_ENABLE ; 
 int /*<<< orphan*/  SMB_HOST_ADDRESS ; 
 int /*<<< orphan*/  SMB_HOST_BLOCK_DATA ; 
 int /*<<< orphan*/  SMB_HOST_COMMAND ; 
 int /*<<< orphan*/  SMB_HOST_DATA ; 
 int amd756_transaction (struct i2c_adapter*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int inb_p (int /*<<< orphan*/ ) ; 
 int inw_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb_p (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outw_p (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 amd756_access(struct i2c_adapter * adap, u16 addr,
		  unsigned short flags, char read_write,
		  u8 command, int size, union i2c_smbus_data * data)
{
	int i, len;
	int status;

	switch (size) {
	case I2C_SMBUS_QUICK:
		outw_p(((addr & 0x7f) << 1) | (read_write & 0x01),
		       SMB_HOST_ADDRESS);
		size = AMD756_QUICK;
		break;
	case I2C_SMBUS_BYTE:
		outw_p(((addr & 0x7f) << 1) | (read_write & 0x01),
		       SMB_HOST_ADDRESS);
		if (read_write == I2C_SMBUS_WRITE)
			outb_p(command, SMB_HOST_DATA);
		size = AMD756_BYTE;
		break;
	case I2C_SMBUS_BYTE_DATA:
		outw_p(((addr & 0x7f) << 1) | (read_write & 0x01),
		       SMB_HOST_ADDRESS);
		outb_p(command, SMB_HOST_COMMAND);
		if (read_write == I2C_SMBUS_WRITE)
			outw_p(data->byte, SMB_HOST_DATA);
		size = AMD756_BYTE_DATA;
		break;
	case I2C_SMBUS_WORD_DATA:
		outw_p(((addr & 0x7f) << 1) | (read_write & 0x01),
		       SMB_HOST_ADDRESS);
		outb_p(command, SMB_HOST_COMMAND);
		if (read_write == I2C_SMBUS_WRITE)
			outw_p(data->word, SMB_HOST_DATA);	/* TODO: endian???? */
		size = AMD756_WORD_DATA;
		break;
	case I2C_SMBUS_BLOCK_DATA:
		outw_p(((addr & 0x7f) << 1) | (read_write & 0x01),
		       SMB_HOST_ADDRESS);
		outb_p(command, SMB_HOST_COMMAND);
		if (read_write == I2C_SMBUS_WRITE) {
			len = data->block[0];
			if (len < 0)
				len = 0;
			if (len > 32)
				len = 32;
			outw_p(len, SMB_HOST_DATA);
			/* i = inw_p(SMBHSTCNT); Reset SMBBLKDAT */
			for (i = 1; i <= len; i++)
				outb_p(data->block[i],
				       SMB_HOST_BLOCK_DATA);
		}
		size = AMD756_BLOCK_DATA;
		break;
	default:
		dev_warn(&adap->dev, "Unsupported transaction %d\n", size);
		return -EOPNOTSUPP;
	}

	/* How about enabling interrupts... */
	outw_p(size & GE_CYC_TYPE_MASK, SMB_GLOBAL_ENABLE);

	status = amd756_transaction(adap);
	if (status)
		return status;

	if ((read_write == I2C_SMBUS_WRITE) || (size == AMD756_QUICK))
		return 0;


	switch (size) {
	case AMD756_BYTE:
		data->byte = inw_p(SMB_HOST_DATA);
		break;
	case AMD756_BYTE_DATA:
		data->byte = inw_p(SMB_HOST_DATA);
		break;
	case AMD756_WORD_DATA:
		data->word = inw_p(SMB_HOST_DATA);	/* TODO: endian???? */
		break;
	case AMD756_BLOCK_DATA:
		data->block[0] = inw_p(SMB_HOST_DATA) & 0x3f;
		if(data->block[0] > 32)
			data->block[0] = 32;
		/* i = inw_p(SMBHSTCNT); Reset SMBBLKDAT */
		for (i = 1; i <= data->block[0]; i++)
			data->block[i] = inb_p(SMB_HOST_BLOCK_DATA);
		break;
	}

	return 0;
}