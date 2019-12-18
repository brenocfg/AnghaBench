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
union i2c_smbus_data {int* block; } ;
struct i2c_adapter {int /*<<< orphan*/  timeout; } ;
struct i801_priv {int features; int is_read; int cmd; int len; int* data; int status; TYPE_1__* pci_dev; int /*<<< orphan*/  waitq; scalar_t__ count; struct i2c_adapter adapter; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int EPROTO ; 
 int ETIMEDOUT ; 
 int FEATURE_IRQ ; 
 int I2C_SMBUS_BLOCK_MAX ; 
 int I2C_SMBUS_BLOCK_PROC_CALL ; 
 int I2C_SMBUS_I2C_BLOCK_DATA ; 
 char I2C_SMBUS_READ ; 
 char I2C_SMBUS_WRITE ; 
 int I801_BLOCK_DATA ; 
 int I801_I2C_BLOCK_DATA ; 
 int /*<<< orphan*/  SMBBLKDAT (struct i801_priv*) ; 
 int /*<<< orphan*/  SMBHSTCNT (struct i801_priv*) ; 
 int SMBHSTCNT_INTREN ; 
 int SMBHSTCNT_LAST_BYTE ; 
 int SMBHSTCNT_START ; 
 int /*<<< orphan*/  SMBHSTDAT0 (struct i801_priv*) ; 
 int /*<<< orphan*/  SMBHSTSTS (struct i801_priv*) ; 
 int SMBHSTSTS_BYTE_DONE ; 
 int SMBHSTSTS_HOST_BUSY ; 
 int SMBHSTSTS_INTR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int i801_check_post (struct i801_priv*,int) ; 
 int i801_check_pre (struct i801_priv*) ; 
 int i801_wait_byte_done (struct i801_priv*) ; 
 int i801_wait_intr (struct i801_priv*) ; 
 int inb (int /*<<< orphan*/ ) ; 
 int inb_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb_p (int,int /*<<< orphan*/ ) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i801_block_transaction_byte_by_byte(struct i801_priv *priv,
					       union i2c_smbus_data *data,
					       char read_write, int command,
					       int hwpec)
{
	int i, len;
	int smbcmd;
	int status;
	int result;
	const struct i2c_adapter *adap = &priv->adapter;

	if (command == I2C_SMBUS_BLOCK_PROC_CALL)
		return -EOPNOTSUPP;

	result = i801_check_pre(priv);
	if (result < 0)
		return result;

	len = data->block[0];

	if (read_write == I2C_SMBUS_WRITE) {
		outb_p(len, SMBHSTDAT0(priv));
		outb_p(data->block[1], SMBBLKDAT(priv));
	}

	if (command == I2C_SMBUS_I2C_BLOCK_DATA &&
	    read_write == I2C_SMBUS_READ)
		smbcmd = I801_I2C_BLOCK_DATA;
	else
		smbcmd = I801_BLOCK_DATA;

	if (priv->features & FEATURE_IRQ) {
		priv->is_read = (read_write == I2C_SMBUS_READ);
		if (len == 1 && priv->is_read)
			smbcmd |= SMBHSTCNT_LAST_BYTE;
		priv->cmd = smbcmd | SMBHSTCNT_INTREN;
		priv->len = len;
		priv->count = 0;
		priv->data = &data->block[1];

		outb_p(priv->cmd | SMBHSTCNT_START, SMBHSTCNT(priv));
		result = wait_event_timeout(priv->waitq,
					    (status = priv->status),
					    adap->timeout);
		if (!result) {
			status = -ETIMEDOUT;
			dev_warn(&priv->pci_dev->dev,
				 "Timeout waiting for interrupt!\n");
		}
		priv->status = 0;
		return i801_check_post(priv, status);
	}

	for (i = 1; i <= len; i++) {
		if (i == len && read_write == I2C_SMBUS_READ)
			smbcmd |= SMBHSTCNT_LAST_BYTE;
		outb_p(smbcmd, SMBHSTCNT(priv));

		if (i == 1)
			outb_p(inb(SMBHSTCNT(priv)) | SMBHSTCNT_START,
			       SMBHSTCNT(priv));

		status = i801_wait_byte_done(priv);
		if (status)
			goto exit;

		if (i == 1 && read_write == I2C_SMBUS_READ
		 && command != I2C_SMBUS_I2C_BLOCK_DATA) {
			len = inb_p(SMBHSTDAT0(priv));
			if (len < 1 || len > I2C_SMBUS_BLOCK_MAX) {
				dev_err(&priv->pci_dev->dev,
					"Illegal SMBus block read size %d\n",
					len);
				/* Recover */
				while (inb_p(SMBHSTSTS(priv)) &
				       SMBHSTSTS_HOST_BUSY)
					outb_p(SMBHSTSTS_BYTE_DONE,
					       SMBHSTSTS(priv));
				outb_p(SMBHSTSTS_INTR, SMBHSTSTS(priv));
				return -EPROTO;
			}
			data->block[0] = len;
		}

		/* Retrieve/store value in SMBBLKDAT */
		if (read_write == I2C_SMBUS_READ)
			data->block[i] = inb_p(SMBBLKDAT(priv));
		if (read_write == I2C_SMBUS_WRITE && i+1 <= len)
			outb_p(data->block[i+1], SMBBLKDAT(priv));

		/* signals SMBBLKDAT ready */
		outb_p(SMBHSTSTS_BYTE_DONE, SMBHSTSTS(priv));
	}

	status = i801_wait_intr(priv);
exit:
	return i801_check_post(priv, status);
}