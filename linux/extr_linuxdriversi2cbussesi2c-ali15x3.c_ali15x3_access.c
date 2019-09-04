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
 int ALI15X3_BLOCK_CLR ; 
#define  ALI15X3_BLOCK_DATA 136 
#define  ALI15X3_BYTE 135 
#define  ALI15X3_BYTE_DATA 134 
 int ALI15X3_QUICK ; 
 int ALI15X3_STS_IDLE ; 
#define  ALI15X3_WORD_DATA 133 
 int EOPNOTSUPP ; 
#define  I2C_SMBUS_BLOCK_DATA 132 
#define  I2C_SMBUS_BYTE 131 
#define  I2C_SMBUS_BYTE_DATA 130 
#define  I2C_SMBUS_QUICK 129 
#define  I2C_SMBUS_WORD_DATA 128 
 char I2C_SMBUS_WRITE ; 
 int MAX_TIMEOUT ; 
 int /*<<< orphan*/  SMBBLKDAT ; 
 int /*<<< orphan*/  SMBHSTADD ; 
 int /*<<< orphan*/  SMBHSTCMD ; 
 int /*<<< orphan*/  SMBHSTCNT ; 
 int /*<<< orphan*/  SMBHSTDAT0 ; 
 int /*<<< orphan*/  SMBHSTDAT1 ; 
 int /*<<< orphan*/  SMBHSTSTS ; 
 int ali15x3_transaction (struct i2c_adapter*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int inb_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  outb_p (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 ali15x3_access(struct i2c_adapter * adap, u16 addr,
		   unsigned short flags, char read_write, u8 command,
		   int size, union i2c_smbus_data * data)
{
	int i, len;
	int temp;
	int timeout;

	/* clear all the bits (clear-on-write) */
	outb_p(0xFF, SMBHSTSTS);
	/* make sure SMBus is idle */
	temp = inb_p(SMBHSTSTS);
	for (timeout = 0;
	     (timeout < MAX_TIMEOUT) && !(temp & ALI15X3_STS_IDLE);
	     timeout++) {
		msleep(1);
		temp = inb_p(SMBHSTSTS);
	}
	if (timeout >= MAX_TIMEOUT) {
		dev_err(&adap->dev, "Idle wait Timeout! STS=0x%02x\n", temp);
	}

	switch (size) {
	case I2C_SMBUS_QUICK:
		outb_p(((addr & 0x7f) << 1) | (read_write & 0x01),
		       SMBHSTADD);
		size = ALI15X3_QUICK;
		break;
	case I2C_SMBUS_BYTE:
		outb_p(((addr & 0x7f) << 1) | (read_write & 0x01),
		       SMBHSTADD);
		if (read_write == I2C_SMBUS_WRITE)
			outb_p(command, SMBHSTCMD);
		size = ALI15X3_BYTE;
		break;
	case I2C_SMBUS_BYTE_DATA:
		outb_p(((addr & 0x7f) << 1) | (read_write & 0x01),
		       SMBHSTADD);
		outb_p(command, SMBHSTCMD);
		if (read_write == I2C_SMBUS_WRITE)
			outb_p(data->byte, SMBHSTDAT0);
		size = ALI15X3_BYTE_DATA;
		break;
	case I2C_SMBUS_WORD_DATA:
		outb_p(((addr & 0x7f) << 1) | (read_write & 0x01),
		       SMBHSTADD);
		outb_p(command, SMBHSTCMD);
		if (read_write == I2C_SMBUS_WRITE) {
			outb_p(data->word & 0xff, SMBHSTDAT0);
			outb_p((data->word & 0xff00) >> 8, SMBHSTDAT1);
		}
		size = ALI15X3_WORD_DATA;
		break;
	case I2C_SMBUS_BLOCK_DATA:
		outb_p(((addr & 0x7f) << 1) | (read_write & 0x01),
		       SMBHSTADD);
		outb_p(command, SMBHSTCMD);
		if (read_write == I2C_SMBUS_WRITE) {
			len = data->block[0];
			if (len < 0) {
				len = 0;
				data->block[0] = len;
			}
			if (len > 32) {
				len = 32;
				data->block[0] = len;
			}
			outb_p(len, SMBHSTDAT0);
			/* Reset SMBBLKDAT */
			outb_p(inb_p(SMBHSTCNT) | ALI15X3_BLOCK_CLR, SMBHSTCNT);
			for (i = 1; i <= len; i++)
				outb_p(data->block[i], SMBBLKDAT);
		}
		size = ALI15X3_BLOCK_DATA;
		break;
	default:
		dev_warn(&adap->dev, "Unsupported transaction %d\n", size);
		return -EOPNOTSUPP;
	}

	outb_p(size, SMBHSTCNT);	/* output command */

	temp = ali15x3_transaction(adap);
	if (temp)
		return temp;

	if ((read_write == I2C_SMBUS_WRITE) || (size == ALI15X3_QUICK))
		return 0;


	switch (size) {
	case ALI15X3_BYTE:	/* Result put in SMBHSTDAT0 */
		data->byte = inb_p(SMBHSTDAT0);
		break;
	case ALI15X3_BYTE_DATA:
		data->byte = inb_p(SMBHSTDAT0);
		break;
	case ALI15X3_WORD_DATA:
		data->word = inb_p(SMBHSTDAT0) + (inb_p(SMBHSTDAT1) << 8);
		break;
	case ALI15X3_BLOCK_DATA:
		len = inb_p(SMBHSTDAT0);
		if (len > 32)
			len = 32;
		data->block[0] = len;
		/* Reset SMBBLKDAT */
		outb_p(inb_p(SMBHSTCNT) | ALI15X3_BLOCK_CLR, SMBHSTCNT);
		for (i = 1; i <= data->block[0]; i++) {
			data->block[i] = inb_p(SMBBLKDAT);
			dev_dbg(&adap->dev, "Blk: len=%d, i=%d, data=%02x\n",
				len, i, data->block[i]);
		}
		break;
	}
	return 0;
}