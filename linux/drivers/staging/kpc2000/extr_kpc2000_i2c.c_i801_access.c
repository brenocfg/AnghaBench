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
union i2c_smbus_data {int byte; int word; } ;
typedef  int u8 ;
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct i2c_device {int features; TYPE_1__ adapter; } ;
struct i2c_adapter {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
 int ENABLE_INT9 ; 
 int EOPNOTSUPP ; 
 int FEATURE_SMBUS_PEC ; 
 unsigned short I2C_CLIENT_PEC ; 
#define  I2C_SMBUS_BLOCK_DATA 136 
#define  I2C_SMBUS_BYTE 135 
#define  I2C_SMBUS_BYTE_DATA 134 
#define  I2C_SMBUS_I2C_BLOCK_DATA 133 
#define  I2C_SMBUS_QUICK 132 
 char I2C_SMBUS_READ ; 
#define  I2C_SMBUS_WORD_DATA 131 
 char I2C_SMBUS_WRITE ; 
#define  I801_BYTE 130 
#define  I801_BYTE_DATA 129 
 int I801_QUICK ; 
#define  I801_WORD_DATA 128 
 int /*<<< orphan*/  SMBAUXCTL (struct i2c_device*) ; 
 int SMBAUXCTL_CRC ; 
 int SMBAUXCTL_E32B ; 
 int /*<<< orphan*/  SMBHSTADD (struct i2c_device*) ; 
 int /*<<< orphan*/  SMBHSTCMD (struct i2c_device*) ; 
 int /*<<< orphan*/  SMBHSTDAT0 (struct i2c_device*) ; 
 int /*<<< orphan*/  SMBHSTDAT1 (struct i2c_device*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 struct i2c_device* i2c_get_adapdata (struct i2c_adapter*) ; 
 int i801_block_transaction (struct i2c_device*,union i2c_smbus_data*,char,int,int) ; 
 int i801_transaction (struct i2c_device*,int) ; 
 int inb_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb_p (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 i801_access(struct i2c_adapter *adap, u16 addr, unsigned short flags, char read_write, u8 command, int size, union i2c_smbus_data *data)
{
	int hwpec;
	int block = 0;
	int ret, xact = 0;
	struct i2c_device *priv = i2c_get_adapdata(adap);

	hwpec = (priv->features & FEATURE_SMBUS_PEC) && (flags & I2C_CLIENT_PEC) && size != I2C_SMBUS_QUICK && size != I2C_SMBUS_I2C_BLOCK_DATA;

	switch (size) {
	case I2C_SMBUS_QUICK:
		dev_dbg(&priv->adapter.dev, "  [acc] SMBUS_QUICK\n");
		outb_p(((addr & 0x7f) << 1) | (read_write & 0x01), SMBHSTADD(priv));
		xact = I801_QUICK;
		break;
	case I2C_SMBUS_BYTE:
		dev_dbg(&priv->adapter.dev, "  [acc] SMBUS_BYTE\n");

		outb_p(((addr & 0x7f) << 1) | (read_write & 0x01), SMBHSTADD(priv));
		if (read_write == I2C_SMBUS_WRITE)
			outb_p(command, SMBHSTCMD(priv));
		xact = I801_BYTE;
		break;
	case I2C_SMBUS_BYTE_DATA:
		dev_dbg(&priv->adapter.dev, "  [acc] SMBUS_BYTE_DATA\n");
		outb_p(((addr & 0x7f) << 1) | (read_write & 0x01), SMBHSTADD(priv));
		outb_p(command, SMBHSTCMD(priv));
		if (read_write == I2C_SMBUS_WRITE)
			outb_p(data->byte, SMBHSTDAT0(priv));
		xact = I801_BYTE_DATA;
		break;
	case I2C_SMBUS_WORD_DATA:
		dev_dbg(&priv->adapter.dev, "  [acc] SMBUS_WORD_DATA\n");
		outb_p(((addr & 0x7f) << 1) | (read_write & 0x01), SMBHSTADD(priv));
		outb_p(command, SMBHSTCMD(priv));
		if (read_write == I2C_SMBUS_WRITE) {
			outb_p(data->word & 0xff, SMBHSTDAT0(priv));
			outb_p((data->word & 0xff00) >> 8, SMBHSTDAT1(priv));
		}
		xact = I801_WORD_DATA;
		break;
	case I2C_SMBUS_BLOCK_DATA:
		dev_dbg(&priv->adapter.dev, "  [acc] SMBUS_BLOCK_DATA\n");
		outb_p(((addr & 0x7f) << 1) | (read_write & 0x01), SMBHSTADD(priv));
		outb_p(command, SMBHSTCMD(priv));
		block = 1;
		break;
	case I2C_SMBUS_I2C_BLOCK_DATA:
		dev_dbg(&priv->adapter.dev, "  [acc] SMBUS_I2C_BLOCK_DATA\n");
		/* NB: page 240 of ICH5 datasheet shows that the R/#W
		 * bit should be cleared here, even when reading
		 */
		outb_p((addr & 0x7f) << 1, SMBHSTADD(priv));
		if (read_write == I2C_SMBUS_READ) {
			/* NB: page 240 of ICH5 datasheet also shows
			 * that DATA1 is the cmd field when reading
			 */
			outb_p(command, SMBHSTDAT1(priv));
		} else {
			outb_p(command, SMBHSTCMD(priv));
		}
		block = 1;
		break;
	default:
		dev_dbg(&priv->adapter.dev, "  [acc] Unsupported transaction %d\n", size);
		return -EOPNOTSUPP;
	}

	if (hwpec) { /* enable/disable hardware PEC */
		dev_dbg(&priv->adapter.dev, "  [acc] hwpec: yes\n");
		outb_p(inb_p(SMBAUXCTL(priv)) | SMBAUXCTL_CRC, SMBAUXCTL(priv));
	} else {
		dev_dbg(&priv->adapter.dev, "  [acc] hwpec: no\n");
		outb_p(inb_p(SMBAUXCTL(priv)) & (~SMBAUXCTL_CRC), SMBAUXCTL(priv));
	}

	if (block) {
		//ret = 0;
		dev_dbg(&priv->adapter.dev, "  [acc] block: yes\n");
		ret = i801_block_transaction(priv, data, read_write, size, hwpec);
	} else {
		dev_dbg(&priv->adapter.dev, "  [acc] block: no\n");
		ret = i801_transaction(priv, xact | ENABLE_INT9);
	}

	/* Some BIOSes don't like it when PEC is enabled at reboot or resume
	 * time, so we forcibly disable it after every transaction. Turn off
	 * E32B for the same reason.
	 */
	if (hwpec || block) {
		dev_dbg(&priv->adapter.dev, "  [acc] hwpec || block\n");
		outb_p(inb_p(SMBAUXCTL(priv)) & ~(SMBAUXCTL_CRC | SMBAUXCTL_E32B), SMBAUXCTL(priv));
	}
	if (block) {
		dev_dbg(&priv->adapter.dev, "  [acc] block\n");
		return ret;
	}
	if (ret) {
		dev_dbg(&priv->adapter.dev, "  [acc] ret %d\n", ret);
		return ret;
	}
	if ((read_write == I2C_SMBUS_WRITE) || (xact == I801_QUICK)) {
		dev_dbg(&priv->adapter.dev, "  [acc] I2C_SMBUS_WRITE || I801_QUICK  -> ret 0\n");
		return 0;
	}

	switch (xact & 0x7f) {
	case I801_BYTE:  /* Result put in SMBHSTDAT0 */
	case I801_BYTE_DATA:
		dev_dbg(&priv->adapter.dev, "  [acc] I801_BYTE or I801_BYTE_DATA\n");
		data->byte = inb_p(SMBHSTDAT0(priv));
		break;
	case I801_WORD_DATA:
		dev_dbg(&priv->adapter.dev, "  [acc] I801_WORD_DATA\n");
		data->word = inb_p(SMBHSTDAT0(priv)) + (inb_p(SMBHSTDAT1(priv)) << 8);
		break;
	}
	return 0;
}