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
typedef  int u8 ;
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  RV3028_CTRL1 ; 
 int RV3028_CTRL1_EERD ; 
 int /*<<< orphan*/  RV3028_EEBUSY_POLL ; 
 int /*<<< orphan*/  RV3028_EEBUSY_TIMEOUT ; 
 int /*<<< orphan*/  RV3028_EEPROM_ADDR ; 
 int /*<<< orphan*/  RV3028_EEPROM_CMD ; 
 int RV3028_EEPROM_CMD_WRITE ; 
 int /*<<< orphan*/  RV3028_EEPROM_DATA ; 
 int /*<<< orphan*/  RV3028_STATUS ; 
 int RV3028_STATUS_EEBUSY ; 
 int regmap_read (void*,int /*<<< orphan*/ ,int*) ; 
 int regmap_read_poll_timeout (void*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_update_bits (void*,int /*<<< orphan*/ ,int,int) ; 
 int regmap_write (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rv3028_eeprom_write(void *priv, unsigned int offset, void *val,
			       size_t bytes)
{
	u32 status, ctrl1;
	int i, ret, err;
	u8 *buf = val;

	ret = regmap_read(priv, RV3028_CTRL1, &ctrl1);
	if (ret)
		return ret;

	if (!(ctrl1 & RV3028_CTRL1_EERD)) {
		ret = regmap_update_bits(priv, RV3028_CTRL1,
					 RV3028_CTRL1_EERD, RV3028_CTRL1_EERD);
		if (ret)
			return ret;

		ret = regmap_read_poll_timeout(priv, RV3028_STATUS, status,
					       !(status & RV3028_STATUS_EEBUSY),
					       RV3028_EEBUSY_POLL,
					       RV3028_EEBUSY_TIMEOUT);
		if (ret)
			goto restore_eerd;
	}

	for (i = 0; i < bytes; i++) {
		ret = regmap_write(priv, RV3028_EEPROM_ADDR, offset + i);
		if (ret)
			goto restore_eerd;

		ret = regmap_write(priv, RV3028_EEPROM_DATA, buf[i]);
		if (ret)
			goto restore_eerd;

		ret = regmap_write(priv, RV3028_EEPROM_CMD, 0x0);
		if (ret)
			goto restore_eerd;

		ret = regmap_write(priv, RV3028_EEPROM_CMD,
				   RV3028_EEPROM_CMD_WRITE);
		if (ret)
			goto restore_eerd;

		usleep_range(RV3028_EEBUSY_POLL, RV3028_EEBUSY_TIMEOUT);

		ret = regmap_read_poll_timeout(priv, RV3028_STATUS, status,
					       !(status & RV3028_STATUS_EEBUSY),
					       RV3028_EEBUSY_POLL,
					       RV3028_EEBUSY_TIMEOUT);
		if (ret)
			goto restore_eerd;
	}

restore_eerd:
	if (!(ctrl1 & RV3028_CTRL1_EERD))
	{
		err = regmap_update_bits(priv, RV3028_CTRL1, RV3028_CTRL1_EERD,
					 0);
		if (err && !ret)
			ret = err;
	}

	return ret;
}