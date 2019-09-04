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
union i2c_smbus_data {scalar_t__ byte; scalar_t__ word; int* block; } ;
typedef  size_t u8 ;
typedef  scalar_t__ u16 ;
struct stub_chip {size_t pointer; size_t bank_reg; int bank_sel; int bank_shift; int bank_mask; int* words; int /*<<< orphan*/  bank_words; } ;
struct smbus_block_data {int len; int* block; } ;
struct i2c_adapter {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  EOPNOTSUPP ; 
#define  I2C_SMBUS_BLOCK_DATA 133 
 int I2C_SMBUS_BLOCK_MAX ; 
#define  I2C_SMBUS_BYTE 132 
#define  I2C_SMBUS_BYTE_DATA 131 
#define  I2C_SMBUS_I2C_BLOCK_DATA 130 
#define  I2C_SMBUS_QUICK 129 
#define  I2C_SMBUS_WORD_DATA 128 
 char I2C_SMBUS_WRITE ; 
 scalar_t__* chip_addr ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 struct stub_chip* stub_chips ; 
 int stub_chips_nr ; 
 struct smbus_block_data* stub_find_block (int /*<<< orphan*/ *,struct stub_chip*,size_t,int) ; 
 scalar_t__* stub_get_wordp (struct stub_chip*,size_t) ; 

__attribute__((used)) static s32 stub_xfer(struct i2c_adapter *adap, u16 addr, unsigned short flags,
	char read_write, u8 command, int size, union i2c_smbus_data *data)
{
	s32 ret;
	int i, len;
	struct stub_chip *chip = NULL;
	struct smbus_block_data *b;
	u16 *wordp;

	/* Search for the right chip */
	for (i = 0; i < stub_chips_nr; i++) {
		if (addr == chip_addr[i]) {
			chip = stub_chips + i;
			break;
		}
	}
	if (!chip)
		return -ENODEV;

	switch (size) {

	case I2C_SMBUS_QUICK:
		dev_dbg(&adap->dev, "smbus quick - addr 0x%02x\n", addr);
		ret = 0;
		break;

	case I2C_SMBUS_BYTE:
		if (read_write == I2C_SMBUS_WRITE) {
			chip->pointer = command;
			dev_dbg(&adap->dev,
				"smbus byte - addr 0x%02x, wrote 0x%02x.\n",
				addr, command);
		} else {
			wordp = stub_get_wordp(chip, chip->pointer++);
			data->byte = *wordp & 0xff;
			dev_dbg(&adap->dev,
				"smbus byte - addr 0x%02x, read  0x%02x.\n",
				addr, data->byte);
		}

		ret = 0;
		break;

	case I2C_SMBUS_BYTE_DATA:
		wordp = stub_get_wordp(chip, command);
		if (read_write == I2C_SMBUS_WRITE) {
			*wordp &= 0xff00;
			*wordp |= data->byte;
			dev_dbg(&adap->dev,
				"smbus byte data - addr 0x%02x, wrote 0x%02x at 0x%02x.\n",
				addr, data->byte, command);

			/* Set the bank as needed */
			if (chip->bank_words && command == chip->bank_reg) {
				chip->bank_sel =
					(data->byte >> chip->bank_shift)
					& chip->bank_mask;
				dev_dbg(&adap->dev,
					"switching to bank %u.\n",
					chip->bank_sel);
			}
		} else {
			data->byte = *wordp & 0xff;
			dev_dbg(&adap->dev,
				"smbus byte data - addr 0x%02x, read  0x%02x at 0x%02x.\n",
				addr, data->byte, command);
		}
		chip->pointer = command + 1;

		ret = 0;
		break;

	case I2C_SMBUS_WORD_DATA:
		wordp = stub_get_wordp(chip, command);
		if (read_write == I2C_SMBUS_WRITE) {
			*wordp = data->word;
			dev_dbg(&adap->dev,
				"smbus word data - addr 0x%02x, wrote 0x%04x at 0x%02x.\n",
				addr, data->word, command);
		} else {
			data->word = *wordp;
			dev_dbg(&adap->dev,
				"smbus word data - addr 0x%02x, read  0x%04x at 0x%02x.\n",
				addr, data->word, command);
		}

		ret = 0;
		break;

	case I2C_SMBUS_I2C_BLOCK_DATA:
		/*
		 * We ignore banks here, because banked chips don't use I2C
		 * block transfers
		 */
		if (data->block[0] > 256 - command)	/* Avoid overrun */
			data->block[0] = 256 - command;
		len = data->block[0];
		if (read_write == I2C_SMBUS_WRITE) {
			for (i = 0; i < len; i++) {
				chip->words[command + i] &= 0xff00;
				chip->words[command + i] |= data->block[1 + i];
			}
			dev_dbg(&adap->dev,
				"i2c block data - addr 0x%02x, wrote %d bytes at 0x%02x.\n",
				addr, len, command);
		} else {
			for (i = 0; i < len; i++) {
				data->block[1 + i] =
					chip->words[command + i] & 0xff;
			}
			dev_dbg(&adap->dev,
				"i2c block data - addr 0x%02x, read  %d bytes at 0x%02x.\n",
				addr, len, command);
		}

		ret = 0;
		break;

	case I2C_SMBUS_BLOCK_DATA:
		/*
		 * We ignore banks here, because chips typically don't use both
		 * banks and SMBus block transfers
		 */
		b = stub_find_block(&adap->dev, chip, command, false);
		if (read_write == I2C_SMBUS_WRITE) {
			len = data->block[0];
			if (len == 0 || len > I2C_SMBUS_BLOCK_MAX) {
				ret = -EINVAL;
				break;
			}
			if (b == NULL) {
				b = stub_find_block(&adap->dev, chip, command,
						    true);
				if (b == NULL) {
					ret = -ENOMEM;
					break;
				}
			}
			/* Largest write sets read block length */
			if (len > b->len)
				b->len = len;
			for (i = 0; i < len; i++)
				b->block[i] = data->block[i + 1];
			/* update for byte and word commands */
			chip->words[command] = (b->block[0] << 8) | b->len;
			dev_dbg(&adap->dev,
				"smbus block data - addr 0x%02x, wrote %d bytes at 0x%02x.\n",
				addr, len, command);
		} else {
			if (b == NULL) {
				dev_dbg(&adap->dev,
					"SMBus block read command without prior block write not supported\n");
				ret = -EOPNOTSUPP;
				break;
			}
			len = b->len;
			data->block[0] = len;
			for (i = 0; i < len; i++)
				data->block[i + 1] = b->block[i];
			dev_dbg(&adap->dev,
				"smbus block data - addr 0x%02x, read  %d bytes at 0x%02x.\n",
				addr, len, command);
		}

		ret = 0;
		break;

	default:
		dev_dbg(&adap->dev, "Unsupported I2C/SMBus command\n");
		ret = -EOPNOTSUPP;
		break;
	} /* switch (size) */

	return ret;
}