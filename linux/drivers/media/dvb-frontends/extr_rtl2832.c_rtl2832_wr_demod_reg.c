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
typedef  int u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct rtl2832_dev {int /*<<< orphan*/  regmap; struct i2c_client* client; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int msb; int lsb; int /*<<< orphan*/  start_address; } ;

/* Variables and functions */
 int REG_MASK (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 TYPE_1__* registers ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int regmap_bulk_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int rtl2832_wr_demod_reg(struct rtl2832_dev *dev, int reg, u32 val)
{
	struct i2c_client *client = dev->client;
	int ret, i;
	u16 reg_start_addr;
	u8 msb, lsb, reading[4], writing[4], len;
	u32 reading_tmp, writing_tmp, mask;

	reg_start_addr = registers[reg].start_address;
	msb = registers[reg].msb;
	lsb = registers[reg].lsb;
	len = (msb >> 3) + 1;
	mask = REG_MASK(msb - lsb);

	ret = regmap_bulk_read(dev->regmap, reg_start_addr, reading, len);
	if (ret)
		goto err;

	reading_tmp = 0;
	for (i = 0; i < len; i++)
		reading_tmp |= reading[i] << ((len - 1 - i) * 8);

	writing_tmp = reading_tmp & ~(mask << lsb);
	writing_tmp |= ((val & mask) << lsb);

	for (i = 0; i < len; i++)
		writing[i] = (writing_tmp >> ((len - 1 - i) * 8)) & 0xff;

	ret = regmap_bulk_write(dev->regmap, reg_start_addr, writing, len);
	if (ret)
		goto err;

	return 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	return ret;
}