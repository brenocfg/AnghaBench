#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
union i2c_smbus_data {int* block; } ;
struct i801_priv {int features; TYPE_1__* pci_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int FEATURE_BLOCK_BUFFER ; 
 int FEATURE_I2C_BLOCK_READ ; 
 int I2C_SMBUS_BLOCK_MAX ; 
 int I2C_SMBUS_I2C_BLOCK_DATA ; 
 char I2C_SMBUS_WRITE ; 
 int /*<<< orphan*/  SMBHSTCFG ; 
 unsigned char SMBHSTCFG_I2C_EN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i801_block_transaction_by_block (struct i801_priv*,union i2c_smbus_data*,char,int,int) ; 
 int i801_block_transaction_byte_by_byte (struct i801_priv*,union i2c_smbus_data*,char,int,int) ; 
 scalar_t__ i801_set_block_buffer_mode (struct i801_priv*) ; 
 int /*<<< orphan*/  pci_read_config_byte (TYPE_1__*,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  pci_write_config_byte (TYPE_1__*,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static int i801_block_transaction(struct i801_priv *priv,
				  union i2c_smbus_data *data, char read_write,
				  int command, int hwpec)
{
	int result = 0;
	unsigned char hostc;

	if (command == I2C_SMBUS_I2C_BLOCK_DATA) {
		if (read_write == I2C_SMBUS_WRITE) {
			/* set I2C_EN bit in configuration register */
			pci_read_config_byte(priv->pci_dev, SMBHSTCFG, &hostc);
			pci_write_config_byte(priv->pci_dev, SMBHSTCFG,
					      hostc | SMBHSTCFG_I2C_EN);
		} else if (!(priv->features & FEATURE_I2C_BLOCK_READ)) {
			dev_err(&priv->pci_dev->dev,
				"I2C block read is unsupported!\n");
			return -EOPNOTSUPP;
		}
	}

	if (read_write == I2C_SMBUS_WRITE
	 || command == I2C_SMBUS_I2C_BLOCK_DATA) {
		if (data->block[0] < 1)
			data->block[0] = 1;
		if (data->block[0] > I2C_SMBUS_BLOCK_MAX)
			data->block[0] = I2C_SMBUS_BLOCK_MAX;
	} else {
		data->block[0] = 32;	/* max for SMBus block reads */
	}

	/* Experience has shown that the block buffer can only be used for
	   SMBus (not I2C) block transactions, even though the datasheet
	   doesn't mention this limitation. */
	if ((priv->features & FEATURE_BLOCK_BUFFER)
	 && command != I2C_SMBUS_I2C_BLOCK_DATA
	 && i801_set_block_buffer_mode(priv) == 0)
		result = i801_block_transaction_by_block(priv, data,
							 read_write,
							 command, hwpec);
	else
		result = i801_block_transaction_byte_by_byte(priv, data,
							     read_write,
							     command, hwpec);

	if (command == I2C_SMBUS_I2C_BLOCK_DATA
	 && read_write == I2C_SMBUS_WRITE) {
		/* restore saved configuration register value */
		pci_write_config_byte(priv->pci_dev, SMBHSTCFG, hostc);
	}
	return result;
}