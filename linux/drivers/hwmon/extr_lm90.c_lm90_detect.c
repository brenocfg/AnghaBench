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
struct i2c_client {int addr; struct i2c_adapter* adapter; } ;
struct i2c_board_info {int /*<<< orphan*/  type; int /*<<< orphan*/  flags; } ;
struct i2c_adapter {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  I2C_CLIENT_PEC ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
 int /*<<< orphan*/  LM90_REG_R_CHIP_ID ; 
 int /*<<< orphan*/  LM90_REG_R_CONFIG1 ; 
 int /*<<< orphan*/  LM90_REG_R_CONFIG2 ; 
 int /*<<< orphan*/  LM90_REG_R_CONVRATE ; 
 int /*<<< orphan*/  LM90_REG_R_MAN_ID ; 
 int /*<<< orphan*/  MAX6659_REG_R_REMOTE_EMERG ; 
 int /*<<< orphan*/  MAX6696_REG_R_STATUS2 ; 
 int /*<<< orphan*/  TMP451_REG_R_LOCAL_TEMPL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lm90_detect(struct i2c_client *client,
		       struct i2c_board_info *info)
{
	struct i2c_adapter *adapter = client->adapter;
	int address = client->addr;
	const char *name = NULL;
	int man_id, chip_id, config1, config2, convrate;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		return -ENODEV;

	/* detection and identification */
	man_id = i2c_smbus_read_byte_data(client, LM90_REG_R_MAN_ID);
	chip_id = i2c_smbus_read_byte_data(client, LM90_REG_R_CHIP_ID);
	config1 = i2c_smbus_read_byte_data(client, LM90_REG_R_CONFIG1);
	convrate = i2c_smbus_read_byte_data(client, LM90_REG_R_CONVRATE);
	if (man_id < 0 || chip_id < 0 || config1 < 0 || convrate < 0)
		return -ENODEV;

	if (man_id == 0x01 || man_id == 0x5C || man_id == 0x41) {
		config2 = i2c_smbus_read_byte_data(client, LM90_REG_R_CONFIG2);
		if (config2 < 0)
			return -ENODEV;
	} else
		config2 = 0;		/* Make compiler happy */

	if ((address == 0x4C || address == 0x4D)
	 && man_id == 0x01) { /* National Semiconductor */
		if ((config1 & 0x2A) == 0x00
		 && (config2 & 0xF8) == 0x00
		 && convrate <= 0x09) {
			if (address == 0x4C
			 && (chip_id & 0xF0) == 0x20) { /* LM90 */
				name = "lm90";
			} else
			if ((chip_id & 0xF0) == 0x30) { /* LM89/LM99 */
				name = "lm99";
				dev_info(&adapter->dev,
					 "Assuming LM99 chip at 0x%02x\n",
					 address);
				dev_info(&adapter->dev,
					 "If it is an LM89, instantiate it "
					 "with the new_device sysfs "
					 "interface\n");
			} else
			if (address == 0x4C
			 && (chip_id & 0xF0) == 0x10) { /* LM86 */
				name = "lm86";
			}
		}
	} else
	if ((address == 0x4C || address == 0x4D)
	 && man_id == 0x41) { /* Analog Devices */
		if ((chip_id & 0xF0) == 0x40 /* ADM1032 */
		 && (config1 & 0x3F) == 0x00
		 && convrate <= 0x0A) {
			name = "adm1032";
			/*
			 * The ADM1032 supports PEC, but only if combined
			 * transactions are not used.
			 */
			if (i2c_check_functionality(adapter,
						    I2C_FUNC_SMBUS_BYTE))
				info->flags |= I2C_CLIENT_PEC;
		} else
		if (chip_id == 0x51 /* ADT7461 */
		 && (config1 & 0x1B) == 0x00
		 && convrate <= 0x0A) {
			name = "adt7461";
		} else
		if (chip_id == 0x57 /* ADT7461A, NCT1008 */
		 && (config1 & 0x1B) == 0x00
		 && convrate <= 0x0A) {
			name = "adt7461a";
		}
	} else
	if (man_id == 0x4D) { /* Maxim */
		int emerg, emerg2, status2;

		/*
		 * We read MAX6659_REG_R_REMOTE_EMERG twice, and re-read
		 * LM90_REG_R_MAN_ID in between. If MAX6659_REG_R_REMOTE_EMERG
		 * exists, both readings will reflect the same value. Otherwise,
		 * the readings will be different.
		 */
		emerg = i2c_smbus_read_byte_data(client,
						 MAX6659_REG_R_REMOTE_EMERG);
		man_id = i2c_smbus_read_byte_data(client,
						  LM90_REG_R_MAN_ID);
		emerg2 = i2c_smbus_read_byte_data(client,
						  MAX6659_REG_R_REMOTE_EMERG);
		status2 = i2c_smbus_read_byte_data(client,
						   MAX6696_REG_R_STATUS2);
		if (emerg < 0 || man_id < 0 || emerg2 < 0 || status2 < 0)
			return -ENODEV;

		/*
		 * The MAX6657, MAX6658 and MAX6659 do NOT have a chip_id
		 * register. Reading from that address will return the last
		 * read value, which in our case is those of the man_id
		 * register. Likewise, the config1 register seems to lack a
		 * low nibble, so the value will be those of the previous
		 * read, so in our case those of the man_id register.
		 * MAX6659 has a third set of upper temperature limit registers.
		 * Those registers also return values on MAX6657 and MAX6658,
		 * thus the only way to detect MAX6659 is by its address.
		 * For this reason it will be mis-detected as MAX6657 if its
		 * address is 0x4C.
		 */
		if (chip_id == man_id
		 && (address == 0x4C || address == 0x4D || address == 0x4E)
		 && (config1 & 0x1F) == (man_id & 0x0F)
		 && convrate <= 0x09) {
			if (address == 0x4C)
				name = "max6657";
			else
				name = "max6659";
		} else
		/*
		 * Even though MAX6695 and MAX6696 do not have a chip ID
		 * register, reading it returns 0x01. Bit 4 of the config1
		 * register is unused and should return zero when read. Bit 0 of
		 * the status2 register is unused and should return zero when
		 * read.
		 *
		 * MAX6695 and MAX6696 have an additional set of temperature
		 * limit registers. We can detect those chips by checking if
		 * one of those registers exists.
		 */
		if (chip_id == 0x01
		 && (config1 & 0x10) == 0x00
		 && (status2 & 0x01) == 0x00
		 && emerg == emerg2
		 && convrate <= 0x07) {
			name = "max6696";
		} else
		/*
		 * The chip_id register of the MAX6680 and MAX6681 holds the
		 * revision of the chip. The lowest bit of the config1 register
		 * is unused and should return zero when read, so should the
		 * second to last bit of config1 (software reset).
		 */
		if (chip_id == 0x01
		 && (config1 & 0x03) == 0x00
		 && convrate <= 0x07) {
			name = "max6680";
		} else
		/*
		 * The chip_id register of the MAX6646/6647/6649 holds the
		 * revision of the chip. The lowest 6 bits of the config1
		 * register are unused and should return zero when read.
		 */
		if (chip_id == 0x59
		 && (config1 & 0x3f) == 0x00
		 && convrate <= 0x07) {
			name = "max6646";
		}
	} else
	if (address == 0x4C
	 && man_id == 0x5C) { /* Winbond/Nuvoton */
		if ((config1 & 0x2A) == 0x00
		 && (config2 & 0xF8) == 0x00) {
			if (chip_id == 0x01 /* W83L771W/G */
			 && convrate <= 0x09) {
				name = "w83l771";
			} else
			if ((chip_id & 0xFE) == 0x10 /* W83L771AWG/ASG */
			 && convrate <= 0x08) {
				name = "w83l771";
			}
		}
	} else
	if (address >= 0x48 && address <= 0x4F
	 && man_id == 0xA1) { /*  NXP Semiconductor/Philips */
		if (chip_id == 0x00
		 && (config1 & 0x2A) == 0x00
		 && (config2 & 0xFE) == 0x00
		 && convrate <= 0x09) {
			name = "sa56004";
		}
	} else
	if ((address == 0x4C || address == 0x4D)
	 && man_id == 0x47) { /* GMT */
		if (chip_id == 0x01 /* G781 */
		 && (config1 & 0x3F) == 0x00
		 && convrate <= 0x08)
			name = "g781";
	} else
	if (address == 0x4C
	 && man_id == 0x55) { /* Texas Instruments */
		int local_ext;

		local_ext = i2c_smbus_read_byte_data(client,
						     TMP451_REG_R_LOCAL_TEMPL);

		if (chip_id == 0x00 /* TMP451 */
		 && (config1 & 0x1B) == 0x00
		 && convrate <= 0x09
		 && (local_ext & 0x0F) == 0x00)
			name = "tmp451";
	}

	if (!name) { /* identification failed */
		dev_dbg(&adapter->dev,
			"Unsupported chip at 0x%02x (man_id=0x%02X, "
			"chip_id=0x%02X)\n", address, man_id, chip_id);
		return -ENODEV;
	}

	strlcpy(info->type, name, I2C_NAME_SIZE);

	return 0;
}