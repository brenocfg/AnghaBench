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
struct rx6110_data {int /*<<< orphan*/  regmap; struct rtc_device* rtc; } ;
struct rtc_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int RX6110_BIT_EXT_TE ; 
 int RX6110_BIT_FLAG_AF ; 
 int RX6110_BIT_FLAG_TF ; 
 int RX6110_BIT_FLAG_UF ; 
 int RX6110_BIT_FLAG_VLF ; 
 int /*<<< orphan*/  RX6110_REG_EXT ; 
 int /*<<< orphan*/  RX6110_REG_FLAG ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int regmap_register_patch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rx6110_default_regs ; 

__attribute__((used)) static int rx6110_init(struct rx6110_data *rx6110)
{
	struct rtc_device *rtc = rx6110->rtc;
	int flags;
	int ret;

	ret = regmap_update_bits(rx6110->regmap, RX6110_REG_EXT,
				 RX6110_BIT_EXT_TE, 0);
	if (ret)
		return ret;

	ret = regmap_register_patch(rx6110->regmap, rx6110_default_regs,
				    ARRAY_SIZE(rx6110_default_regs));
	if (ret)
		return ret;

	ret = regmap_read(rx6110->regmap, RX6110_REG_FLAG, &flags);
	if (ret)
		return ret;

	/* check for VLF Flag (set at power-on) */
	if ((flags & RX6110_BIT_FLAG_VLF))
		dev_warn(&rtc->dev, "Voltage low, data loss detected.\n");

	/* check for Alarm Flag */
	if (flags & RX6110_BIT_FLAG_AF)
		dev_warn(&rtc->dev, "An alarm may have been missed.\n");

	/* check for Periodic Timer Flag */
	if (flags & RX6110_BIT_FLAG_TF)
		dev_warn(&rtc->dev, "Periodic timer was detected\n");

	/* check for Update Timer Flag */
	if (flags & RX6110_BIT_FLAG_UF)
		dev_warn(&rtc->dev, "Update timer was detected\n");

	/* clear all flags BUT VLF */
	ret = regmap_update_bits(rx6110->regmap, RX6110_REG_FLAG,
				 RX6110_BIT_FLAG_AF |
				 RX6110_BIT_FLAG_UF |
				 RX6110_BIT_FLAG_TF,
				 0);

	return ret;
}