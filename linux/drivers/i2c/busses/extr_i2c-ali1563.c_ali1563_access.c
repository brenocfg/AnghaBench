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
typedef  int u32 ;
typedef  int u16 ;
struct i2c_adapter {int /*<<< orphan*/  dev; } ;
typedef  int s32 ;

/* Variables and functions */
 int ALI1563_MAX_TIMEOUT ; 
 int EOPNOTSUPP ; 
#define  HST_CNTL2_BLOCK 136 
#define  HST_CNTL2_BYTE 135 
#define  HST_CNTL2_BYTE_DATA 134 
 int HST_CNTL2_QUICK ; 
 int HST_CNTL2_SIZEMASK ; 
#define  HST_CNTL2_WORD_DATA 133 
 int HST_STS_BUSY ; 
#define  I2C_SMBUS_BLOCK_DATA 132 
#define  I2C_SMBUS_BYTE 131 
#define  I2C_SMBUS_BYTE_DATA 130 
#define  I2C_SMBUS_QUICK 129 
#define  I2C_SMBUS_WORD_DATA 128 
 char I2C_SMBUS_WRITE ; 
 int /*<<< orphan*/  SMB_HST_ADD ; 
 int /*<<< orphan*/  SMB_HST_CMD ; 
 int /*<<< orphan*/  SMB_HST_CNTL2 ; 
 int /*<<< orphan*/  SMB_HST_DAT0 ; 
 int /*<<< orphan*/  SMB_HST_DAT1 ; 
 int /*<<< orphan*/  SMB_HST_STS ; 
 int ali1563_block (struct i2c_adapter*,union i2c_smbus_data*,char) ; 
 int ali1563_transaction (struct i2c_adapter*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int inb_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb_p (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 ali1563_access(struct i2c_adapter *a, u16 addr,
			  unsigned short flags, char rw, u8 cmd,
			  int size, union i2c_smbus_data *data)
{
	int error = 0;
	int timeout;
	u32 reg;

	for (timeout = ALI1563_MAX_TIMEOUT; timeout; timeout--) {
		reg = inb_p(SMB_HST_STS);
		if (!(reg & HST_STS_BUSY))
			break;
	}
	if (!timeout)
		dev_warn(&a->dev, "SMBus not idle. HST_STS = %02x\n", reg);
	outb_p(0xff, SMB_HST_STS);

	/* Map the size to what the chip understands */
	switch (size) {
	case I2C_SMBUS_QUICK:
		size = HST_CNTL2_QUICK;
		break;
	case I2C_SMBUS_BYTE:
		size = HST_CNTL2_BYTE;
		break;
	case I2C_SMBUS_BYTE_DATA:
		size = HST_CNTL2_BYTE_DATA;
		break;
	case I2C_SMBUS_WORD_DATA:
		size = HST_CNTL2_WORD_DATA;
		break;
	case I2C_SMBUS_BLOCK_DATA:
		size = HST_CNTL2_BLOCK;
		break;
	default:
		dev_warn(&a->dev, "Unsupported transaction %d\n", size);
		error = -EOPNOTSUPP;
		goto Done;
	}

	outb_p(((addr & 0x7f) << 1) | (rw & 0x01), SMB_HST_ADD);
	outb_p((inb_p(SMB_HST_CNTL2) & ~HST_CNTL2_SIZEMASK) |
	       (size << 3), SMB_HST_CNTL2);

	/* Write the command register */

	switch (size) {
	case HST_CNTL2_BYTE:
		if (rw == I2C_SMBUS_WRITE)
			/* Beware it uses DAT0 register and not CMD! */
			outb_p(cmd, SMB_HST_DAT0);
		break;
	case HST_CNTL2_BYTE_DATA:
		outb_p(cmd, SMB_HST_CMD);
		if (rw == I2C_SMBUS_WRITE)
			outb_p(data->byte, SMB_HST_DAT0);
		break;
	case HST_CNTL2_WORD_DATA:
		outb_p(cmd, SMB_HST_CMD);
		if (rw == I2C_SMBUS_WRITE) {
			outb_p(data->word & 0xff, SMB_HST_DAT0);
			outb_p((data->word & 0xff00) >> 8, SMB_HST_DAT1);
		}
		break;
	case HST_CNTL2_BLOCK:
		outb_p(cmd, SMB_HST_CMD);
		error = ali1563_block(a, data, rw);
		goto Done;
	}

	error = ali1563_transaction(a, size);
	if (error)
		goto Done;

	if ((rw == I2C_SMBUS_WRITE) || (size == HST_CNTL2_QUICK))
		goto Done;

	switch (size) {
	case HST_CNTL2_BYTE:	/* Result put in SMBHSTDAT0 */
		data->byte = inb_p(SMB_HST_DAT0);
		break;
	case HST_CNTL2_BYTE_DATA:
		data->byte = inb_p(SMB_HST_DAT0);
		break;
	case HST_CNTL2_WORD_DATA:
		data->word = inb_p(SMB_HST_DAT0) + (inb_p(SMB_HST_DAT1) << 8);
		break;
	}
Done:
	return error;
}