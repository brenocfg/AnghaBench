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
struct i801_priv {int features; int original_hstcfg; int /*<<< orphan*/  acpi_lock; TYPE_1__* pci_dev; scalar_t__ acpi_reserved; } ;
struct i2c_adapter {int dummy; } ;
typedef  int s32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int EOPNOTSUPP ; 
 int FEATURE_SMBUS_PEC ; 
 unsigned short I2C_CLIENT_PEC ; 
#define  I2C_SMBUS_BLOCK_DATA 137 
#define  I2C_SMBUS_BLOCK_PROC_CALL 136 
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
 int /*<<< orphan*/  SMBAUXCTL (struct i801_priv*) ; 
 int SMBAUXCTL_CRC ; 
 int SMBAUXCTL_E32B ; 
 int /*<<< orphan*/  SMBHSTADD (struct i801_priv*) ; 
 int SMBHSTCFG_SPD_WD ; 
 int /*<<< orphan*/  SMBHSTCMD (struct i801_priv*) ; 
 int /*<<< orphan*/  SMBHSTDAT0 (struct i801_priv*) ; 
 int /*<<< orphan*/  SMBHSTDAT1 (struct i801_priv*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct i801_priv* i2c_get_adapdata (struct i2c_adapter*) ; 
 int i801_block_transaction (struct i801_priv*,union i2c_smbus_data*,char,int,int) ; 
 int i801_transaction (struct i801_priv*,int) ; 
 int inb_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  outb_p (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ *) ; 

__attribute__((used)) static s32 i801_access(struct i2c_adapter *adap, u16 addr,
		       unsigned short flags, char read_write, u8 command,
		       int size, union i2c_smbus_data *data)
{
	int hwpec;
	int block = 0;
	int ret = 0, xact = 0;
	struct i801_priv *priv = i2c_get_adapdata(adap);

	mutex_lock(&priv->acpi_lock);
	if (priv->acpi_reserved) {
		mutex_unlock(&priv->acpi_lock);
		return -EBUSY;
	}

	pm_runtime_get_sync(&priv->pci_dev->dev);

	hwpec = (priv->features & FEATURE_SMBUS_PEC) && (flags & I2C_CLIENT_PEC)
		&& size != I2C_SMBUS_QUICK
		&& size != I2C_SMBUS_I2C_BLOCK_DATA;

	switch (size) {
	case I2C_SMBUS_QUICK:
		outb_p(((addr & 0x7f) << 1) | (read_write & 0x01),
		       SMBHSTADD(priv));
		xact = I801_QUICK;
		break;
	case I2C_SMBUS_BYTE:
		outb_p(((addr & 0x7f) << 1) | (read_write & 0x01),
		       SMBHSTADD(priv));
		if (read_write == I2C_SMBUS_WRITE)
			outb_p(command, SMBHSTCMD(priv));
		xact = I801_BYTE;
		break;
	case I2C_SMBUS_BYTE_DATA:
		outb_p(((addr & 0x7f) << 1) | (read_write & 0x01),
		       SMBHSTADD(priv));
		outb_p(command, SMBHSTCMD(priv));
		if (read_write == I2C_SMBUS_WRITE)
			outb_p(data->byte, SMBHSTDAT0(priv));
		xact = I801_BYTE_DATA;
		break;
	case I2C_SMBUS_WORD_DATA:
		outb_p(((addr & 0x7f) << 1) | (read_write & 0x01),
		       SMBHSTADD(priv));
		outb_p(command, SMBHSTCMD(priv));
		if (read_write == I2C_SMBUS_WRITE) {
			outb_p(data->word & 0xff, SMBHSTDAT0(priv));
			outb_p((data->word & 0xff00) >> 8, SMBHSTDAT1(priv));
		}
		xact = I801_WORD_DATA;
		break;
	case I2C_SMBUS_BLOCK_DATA:
		outb_p(((addr & 0x7f) << 1) | (read_write & 0x01),
		       SMBHSTADD(priv));
		outb_p(command, SMBHSTCMD(priv));
		block = 1;
		break;
	case I2C_SMBUS_I2C_BLOCK_DATA:
		/*
		 * NB: page 240 of ICH5 datasheet shows that the R/#W
		 * bit should be cleared here, even when reading.
		 * However if SPD Write Disable is set (Lynx Point and later),
		 * the read will fail if we don't set the R/#W bit.
		 */
		outb_p(((addr & 0x7f) << 1) |
		       ((priv->original_hstcfg & SMBHSTCFG_SPD_WD) ?
			(read_write & 0x01) : 0),
		       SMBHSTADD(priv));
		if (read_write == I2C_SMBUS_READ) {
			/* NB: page 240 of ICH5 datasheet also shows
			 * that DATA1 is the cmd field when reading */
			outb_p(command, SMBHSTDAT1(priv));
		} else
			outb_p(command, SMBHSTCMD(priv));
		block = 1;
		break;
	case I2C_SMBUS_BLOCK_PROC_CALL:
		/*
		 * Bit 0 of the slave address register always indicate a write
		 * command.
		 */
		outb_p((addr & 0x7f) << 1, SMBHSTADD(priv));
		outb_p(command, SMBHSTCMD(priv));
		block = 1;
		break;
	default:
		dev_err(&priv->pci_dev->dev, "Unsupported transaction %d\n",
			size);
		ret = -EOPNOTSUPP;
		goto out;
	}

	if (hwpec)	/* enable/disable hardware PEC */
		outb_p(inb_p(SMBAUXCTL(priv)) | SMBAUXCTL_CRC, SMBAUXCTL(priv));
	else
		outb_p(inb_p(SMBAUXCTL(priv)) & (~SMBAUXCTL_CRC),
		       SMBAUXCTL(priv));

	if (block)
		ret = i801_block_transaction(priv, data, read_write, size,
					     hwpec);
	else
		ret = i801_transaction(priv, xact);

	/* Some BIOSes don't like it when PEC is enabled at reboot or resume
	   time, so we forcibly disable it after every transaction. Turn off
	   E32B for the same reason. */
	if (hwpec || block)
		outb_p(inb_p(SMBAUXCTL(priv)) &
		       ~(SMBAUXCTL_CRC | SMBAUXCTL_E32B), SMBAUXCTL(priv));

	if (block)
		goto out;
	if (ret)
		goto out;
	if ((read_write == I2C_SMBUS_WRITE) || (xact == I801_QUICK))
		goto out;

	switch (xact & 0x7f) {
	case I801_BYTE:	/* Result put in SMBHSTDAT0 */
	case I801_BYTE_DATA:
		data->byte = inb_p(SMBHSTDAT0(priv));
		break;
	case I801_WORD_DATA:
		data->word = inb_p(SMBHSTDAT0(priv)) +
			     (inb_p(SMBHSTDAT1(priv)) << 8);
		break;
	}

out:
	pm_runtime_mark_last_busy(&priv->pci_dev->dev);
	pm_runtime_put_autosuspend(&priv->pci_dev->dev);
	mutex_unlock(&priv->acpi_lock);
	return ret;
}