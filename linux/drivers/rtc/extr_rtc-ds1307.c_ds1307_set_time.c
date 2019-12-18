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
struct rtc_time {int tm_sec; int tm_min; int tm_hour; int tm_mday; int tm_mon; int tm_year; int tm_wday; } ;
struct ds1307 {size_t type; int /*<<< orphan*/  regmap; } ;
struct device {int dummy; } ;
struct chip_desc {int century_bit; int century_enable_bit; size_t century_reg; int /*<<< orphan*/  offset; } ;
typedef  int /*<<< orphan*/  regs ;

/* Variables and functions */
 int /*<<< orphan*/  DS1307_REG_CONTROL ; 
 size_t DS1307_REG_HOUR ; 
 size_t DS1307_REG_MDAY ; 
 size_t DS1307_REG_MIN ; 
 size_t DS1307_REG_MONTH ; 
 size_t DS1307_REG_SECS ; 
 size_t DS1307_REG_WDAY ; 
 size_t DS1307_REG_YEAR ; 
 int /*<<< orphan*/  DS1338_BIT_OSF ; 
 int /*<<< orphan*/  DS1340_BIT_OSF ; 
 int /*<<< orphan*/  DS1340_REG_FLAG ; 
 int EINVAL ; 
 int MCP794XX_BIT_ST ; 
 int MCP794XX_BIT_VBATEN ; 
 int /*<<< orphan*/  RX8130_REG_FLAG ; 
 scalar_t__ RX8130_REG_FLAG_VLF ; 
 int bin2bcd (int) ; 
 struct chip_desc* chips ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,char*,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,char*,int) ; 
 struct ds1307* dev_get_drvdata (struct device*) ; 
#define  ds_1308 131 
#define  ds_1338 130 
#define  ds_1340 129 
#define  mcp794xx 128 
 int regmap_bulk_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int rx_8130 ; 

__attribute__((used)) static int ds1307_set_time(struct device *dev, struct rtc_time *t)
{
	struct ds1307	*ds1307 = dev_get_drvdata(dev);
	const struct chip_desc *chip = &chips[ds1307->type];
	int		result;
	int		tmp;
	u8		regs[7];

	dev_dbg(dev, "%s secs=%d, mins=%d, "
		"hours=%d, mday=%d, mon=%d, year=%d, wday=%d\n",
		"write", t->tm_sec, t->tm_min,
		t->tm_hour, t->tm_mday,
		t->tm_mon, t->tm_year, t->tm_wday);

	if (t->tm_year < 100)
		return -EINVAL;

#ifdef CONFIG_RTC_DRV_DS1307_CENTURY
	if (t->tm_year > (chip->century_bit ? 299 : 199))
		return -EINVAL;
#else
	if (t->tm_year > 199)
		return -EINVAL;
#endif

	regs[DS1307_REG_SECS] = bin2bcd(t->tm_sec);
	regs[DS1307_REG_MIN] = bin2bcd(t->tm_min);
	regs[DS1307_REG_HOUR] = bin2bcd(t->tm_hour);
	regs[DS1307_REG_WDAY] = bin2bcd(t->tm_wday + 1);
	regs[DS1307_REG_MDAY] = bin2bcd(t->tm_mday);
	regs[DS1307_REG_MONTH] = bin2bcd(t->tm_mon + 1);

	/* assume 20YY not 19YY */
	tmp = t->tm_year - 100;
	regs[DS1307_REG_YEAR] = bin2bcd(tmp);

	if (chip->century_enable_bit)
		regs[chip->century_reg] |= chip->century_enable_bit;
	if (t->tm_year > 199 && chip->century_bit)
		regs[chip->century_reg] |= chip->century_bit;

	switch (ds1307->type) {
	case ds_1308:
	case ds_1338:
		regmap_update_bits(ds1307->regmap, DS1307_REG_CONTROL,
				   DS1338_BIT_OSF, 0);
		break;
	case ds_1340:
		regmap_update_bits(ds1307->regmap, DS1340_REG_FLAG,
				   DS1340_BIT_OSF, 0);
		break;
	case mcp794xx:
		/*
		 * these bits were cleared when preparing the date/time
		 * values and need to be set again before writing the
		 * regsfer out to the device.
		 */
		regs[DS1307_REG_SECS] |= MCP794XX_BIT_ST;
		regs[DS1307_REG_WDAY] |= MCP794XX_BIT_VBATEN;
		break;
	default:
		break;
	}

	dev_dbg(dev, "%s: %7ph\n", "write", regs);

	result = regmap_bulk_write(ds1307->regmap, chip->offset, regs,
				   sizeof(regs));
	if (result) {
		dev_err(dev, "%s error %d\n", "write", result);
		return result;
	}

	if (ds1307->type == rx_8130) {
		/* clear Voltage Loss Flag as data is available now */
		result = regmap_write(ds1307->regmap, RX8130_REG_FLAG,
				      ~(u8)RX8130_REG_FLAG_VLF);
		if (result) {
			dev_err(dev, "%s error %d\n", "write", result);
			return result;
		}
	}

	return 0;
}