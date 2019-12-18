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
union i2c_smbus_data {int byte; int word; int /*<<< orphan*/ * block; } ;
typedef  int u8 ;
struct ismt_priv {TYPE_1__* pci_dev; int /*<<< orphan*/ * buffer; } ;
struct ismt_desc {int status; int /*<<< orphan*/  rxbytes; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EBADMSG ; 
 int EIO ; 
 int EMSGSIZE ; 
 int ENXIO ; 
 int EPROTO ; 
 int ETIMEDOUT ; 
#define  I2C_SMBUS_BLOCK_DATA 133 
#define  I2C_SMBUS_BYTE 132 
#define  I2C_SMBUS_BYTE_DATA 131 
#define  I2C_SMBUS_I2C_BLOCK_DATA 130 
#define  I2C_SMBUS_PROC_CALL 129 
#define  I2C_SMBUS_WORD_DATA 128 
 char I2C_SMBUS_WRITE ; 
 int ISMT_DESC_CLTO ; 
 int ISMT_DESC_COL ; 
 int ISMT_DESC_CRC ; 
 int ISMT_DESC_DLTO ; 
 int ISMT_DESC_LPR ; 
 int ISMT_DESC_NAK ; 
 int ISMT_DESC_SCS ; 
 int* PTR_ALIGN (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  __ismt_desc_dump (int /*<<< orphan*/ *,struct ismt_desc const*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ismt_gen_reg_dump (struct ismt_priv*) ; 
 int /*<<< orphan*/  ismt_mstr_reg_dump (struct ismt_priv*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ismt_process_desc(const struct ismt_desc *desc,
			     union i2c_smbus_data *data,
			     struct ismt_priv *priv, int size,
			     char read_write)
{
	u8 *dma_buffer = PTR_ALIGN(&priv->buffer[0], 16);

	dev_dbg(&priv->pci_dev->dev, "Processing completed descriptor\n");
	__ismt_desc_dump(&priv->pci_dev->dev, desc);
	ismt_gen_reg_dump(priv);
	ismt_mstr_reg_dump(priv);

	if (desc->status & ISMT_DESC_SCS) {
		if (read_write == I2C_SMBUS_WRITE &&
		    size != I2C_SMBUS_PROC_CALL)
			return 0;

		switch (size) {
		case I2C_SMBUS_BYTE:
		case I2C_SMBUS_BYTE_DATA:
			data->byte = dma_buffer[0];
			break;
		case I2C_SMBUS_WORD_DATA:
		case I2C_SMBUS_PROC_CALL:
			data->word = dma_buffer[0] | (dma_buffer[1] << 8);
			break;
		case I2C_SMBUS_BLOCK_DATA:
			if (desc->rxbytes != dma_buffer[0] + 1)
				return -EMSGSIZE;

			memcpy(data->block, dma_buffer, desc->rxbytes);
			break;
		case I2C_SMBUS_I2C_BLOCK_DATA:
			memcpy(&data->block[1], dma_buffer, desc->rxbytes);
			data->block[0] = desc->rxbytes;
			break;
		}
		return 0;
	}

	if (likely(desc->status & ISMT_DESC_NAK))
		return -ENXIO;

	if (desc->status & ISMT_DESC_CRC)
		return -EBADMSG;

	if (desc->status & ISMT_DESC_COL)
		return -EAGAIN;

	if (desc->status & ISMT_DESC_LPR)
		return -EPROTO;

	if (desc->status & (ISMT_DESC_DLTO | ISMT_DESC_CLTO))
		return -ETIMEDOUT;

	return -EIO;
}