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
typedef  int /*<<< orphan*/  uint32_t ;
struct i2c_id_config_access {int /*<<< orphan*/  bfHW_EngineID; int /*<<< orphan*/  bfI2C_LineMux; int /*<<< orphan*/  bfHW_Capable; } ;
struct graphics_object_i2c_info {int dummy; } ;
struct dc_bios {int dummy; } ;
struct bios_parser {int dummy; } ;
struct atom_i2c_record {int /*<<< orphan*/  i2c_id; } ;
typedef  enum bp_result { ____Placeholder_bp_result } bp_result ;

/* Variables and functions */
 struct bios_parser* BP_FROM_DCB (struct dc_bios*) ; 
 int BP_RESULT_BADINPUT ; 
 int get_gpio_i2c_info (struct bios_parser*,struct atom_i2c_record*,struct graphics_object_i2c_info*) ; 

__attribute__((used)) static enum bp_result bios_parser_get_thermal_ddc_info(
	struct dc_bios *dcb,
	uint32_t i2c_channel_id,
	struct graphics_object_i2c_info *info)
{
	struct bios_parser *bp = BP_FROM_DCB(dcb);
	struct i2c_id_config_access *config;
	struct atom_i2c_record record;

	if (!info)
		return BP_RESULT_BADINPUT;

	config = (struct i2c_id_config_access *) &i2c_channel_id;

	record.i2c_id = config->bfHW_Capable;
	record.i2c_id |= config->bfI2C_LineMux;
	record.i2c_id |= config->bfHW_EngineID;

	return get_gpio_i2c_info(bp, &record, info);
}