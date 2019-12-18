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
struct i801_priv {int cmd; int count; int len; int* data; TYPE_1__* pci_dev; scalar_t__ is_read; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int I2C_SMBUS_BLOCK_MAX ; 
 int I801_BLOCK_DATA ; 
 int /*<<< orphan*/  SMBBLKDAT (struct i801_priv*) ; 
 int /*<<< orphan*/  SMBHSTCNT (struct i801_priv*) ; 
 int SMBHSTCNT_LAST_BYTE ; 
 int /*<<< orphan*/  SMBHSTDAT0 (struct i801_priv*) ; 
 int /*<<< orphan*/  SMBHSTSTS (struct i801_priv*) ; 
 int SMBHSTSTS_BYTE_DONE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int inb (int /*<<< orphan*/ ) ; 
 int inb_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb_p (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i801_isr_byte_done(struct i801_priv *priv)
{
	if (priv->is_read) {
		/* For SMBus block reads, length is received with first byte */
		if (((priv->cmd & 0x1c) == I801_BLOCK_DATA) &&
		    (priv->count == 0)) {
			priv->len = inb_p(SMBHSTDAT0(priv));
			if (priv->len < 1 || priv->len > I2C_SMBUS_BLOCK_MAX) {
				dev_err(&priv->pci_dev->dev,
					"Illegal SMBus block read size %d\n",
					priv->len);
				/* FIXME: Recover */
				priv->len = I2C_SMBUS_BLOCK_MAX;
			} else {
				dev_dbg(&priv->pci_dev->dev,
					"SMBus block read size is %d\n",
					priv->len);
			}
			priv->data[-1] = priv->len;
		}

		/* Read next byte */
		if (priv->count < priv->len)
			priv->data[priv->count++] = inb(SMBBLKDAT(priv));
		else
			dev_dbg(&priv->pci_dev->dev,
				"Discarding extra byte on block read\n");

		/* Set LAST_BYTE for last byte of read transaction */
		if (priv->count == priv->len - 1)
			outb_p(priv->cmd | SMBHSTCNT_LAST_BYTE,
			       SMBHSTCNT(priv));
	} else if (priv->count < priv->len - 1) {
		/* Write next byte, except for IRQ after last byte */
		outb_p(priv->data[++priv->count], SMBBLKDAT(priv));
	}

	/* Clear BYTE_DONE to continue with next byte */
	outb_p(SMBHSTSTS_BYTE_DONE, SMBHSTSTS(priv));
}