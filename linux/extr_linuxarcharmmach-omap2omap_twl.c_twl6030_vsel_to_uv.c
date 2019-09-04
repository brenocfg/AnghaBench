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

/* Variables and functions */
 int /*<<< orphan*/  REG_SMPS_OFFSET ; 
 int /*<<< orphan*/  TWL6030_MODULE_ID0 ; 
 int is_offset_valid ; 
 int smps_offset ; 
 int /*<<< orphan*/  twl_i2c_read_u8 (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long twl6030_vsel_to_uv(const u8 vsel)
{
	/*
	 * In TWL6030 depending on the value of SMPS_OFFSET
	 * efuse register the voltage range supported in
	 * standard mode can be either between 0.6V - 1.3V or
	 * 0.7V - 1.4V. In TWL6030 ES1.0 SMPS_OFFSET efuse
	 * is programmed to all 0's where as starting from
	 * TWL6030 ES1.1 the efuse is programmed to 1
	 */
	if (!is_offset_valid) {
		twl_i2c_read_u8(TWL6030_MODULE_ID0, &smps_offset,
				REG_SMPS_OFFSET);
		is_offset_valid = true;
	}

	if (!vsel)
		return 0;
	/*
	 * There is no specific formula for voltage to vsel
	 * conversion above 1.3V. There are special hardcoded
	 * values for voltages above 1.3V. Currently we are
	 * hardcoding only for 1.35 V which is used for 1GH OPP for
	 * OMAP4430.
	 */
	if (vsel == 0x3A)
		return 1350000;

	if (smps_offset & 0x8)
		return ((((vsel - 1) * 1266) + 70900)) * 10;
	else
		return ((((vsel - 1) * 1266) + 60770)) * 10;
}