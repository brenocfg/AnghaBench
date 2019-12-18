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
typedef  int /*<<< orphan*/  u8 ;
struct rx8010_data {int ctrlreg; int /*<<< orphan*/  client; } ;
struct rtc_time {int tm_year; int tm_sec; int tm_min; int tm_hour; int tm_mday; int tm_mon; int tm_wday; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  RX8010_CTRL ; 
 int RX8010_CTRL_STOP ; 
 int /*<<< orphan*/  RX8010_FLAG ; 
 int RX8010_FLAG_VLF ; 
 size_t RX8010_HOUR ; 
 size_t RX8010_MDAY ; 
 size_t RX8010_MIN ; 
 size_t RX8010_MONTH ; 
 size_t RX8010_SEC ; 
 size_t RX8010_WDAY ; 
 size_t RX8010_YEAR ; 
 int /*<<< orphan*/  bin2bcd (int) ; 
 struct rx8010_data* dev_get_drvdata (struct device*) ; 
 int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int i2c_smbus_write_i2c_block_data (int /*<<< orphan*/ ,size_t,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rx8010_set_time(struct device *dev, struct rtc_time *dt)
{
	struct rx8010_data *rx8010 = dev_get_drvdata(dev);
	u8 date[7];
	int ctrl, flagreg;
	int ret;

	if ((dt->tm_year < 100) || (dt->tm_year > 199))
		return -EINVAL;

	/* set STOP bit before changing clock/calendar */
	ctrl = i2c_smbus_read_byte_data(rx8010->client, RX8010_CTRL);
	if (ctrl < 0)
		return ctrl;
	rx8010->ctrlreg = ctrl | RX8010_CTRL_STOP;
	ret = i2c_smbus_write_byte_data(rx8010->client, RX8010_CTRL,
					rx8010->ctrlreg);
	if (ret < 0)
		return ret;

	date[RX8010_SEC - RX8010_SEC] = bin2bcd(dt->tm_sec);
	date[RX8010_MIN - RX8010_SEC] = bin2bcd(dt->tm_min);
	date[RX8010_HOUR - RX8010_SEC] = bin2bcd(dt->tm_hour);
	date[RX8010_MDAY - RX8010_SEC] = bin2bcd(dt->tm_mday);
	date[RX8010_MONTH - RX8010_SEC] = bin2bcd(dt->tm_mon + 1);
	date[RX8010_YEAR - RX8010_SEC] = bin2bcd(dt->tm_year - 100);
	date[RX8010_WDAY - RX8010_SEC] = bin2bcd(1 << dt->tm_wday);

	ret = i2c_smbus_write_i2c_block_data(rx8010->client,
					     RX8010_SEC, 7, date);
	if (ret < 0)
		return ret;

	/* clear STOP bit after changing clock/calendar */
	ctrl = i2c_smbus_read_byte_data(rx8010->client, RX8010_CTRL);
	if (ctrl < 0)
		return ctrl;
	rx8010->ctrlreg = ctrl & ~RX8010_CTRL_STOP;
	ret = i2c_smbus_write_byte_data(rx8010->client, RX8010_CTRL,
					rx8010->ctrlreg);
	if (ret < 0)
		return ret;

	flagreg = i2c_smbus_read_byte_data(rx8010->client, RX8010_FLAG);
	if (flagreg < 0) {
		return flagreg;
	}

	if (flagreg & RX8010_FLAG_VLF)
		ret = i2c_smbus_write_byte_data(rx8010->client, RX8010_FLAG,
						flagreg & ~RX8010_FLAG_VLF);

	return 0;
}