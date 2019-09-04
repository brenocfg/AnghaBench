#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct graphics_object_i2c_info {int dummy; } ;
struct dc_bios {int dummy; } ;
struct bios_parser {int dummy; } ;
typedef  enum bp_result { ____Placeholder_bp_result } bp_result ;
struct TYPE_6__ {int /*<<< orphan*/  bfHW_EngineID; int /*<<< orphan*/  bfI2C_LineMux; int /*<<< orphan*/  bfHW_Capable; } ;
struct TYPE_9__ {TYPE_1__ sbfAccess; } ;
struct TYPE_7__ {int /*<<< orphan*/  bfHW_EngineID; int /*<<< orphan*/  bfI2C_LineMux; int /*<<< orphan*/  bfHW_Capable; } ;
struct TYPE_8__ {TYPE_2__ sucI2cId; } ;
typedef  TYPE_3__ ATOM_I2C_RECORD ;
typedef  TYPE_4__ ATOM_I2C_ID_CONFIG_ACCESS ;

/* Variables and functions */
 struct bios_parser* BP_FROM_DCB (struct dc_bios*) ; 
 int BP_RESULT_BADINPUT ; 
 int get_gpio_i2c_info (struct bios_parser*,TYPE_3__*,struct graphics_object_i2c_info*) ; 

__attribute__((used)) static enum bp_result bios_parser_get_thermal_ddc_info(
	struct dc_bios *dcb,
	uint32_t i2c_channel_id,
	struct graphics_object_i2c_info *info)
{
	struct bios_parser *bp = BP_FROM_DCB(dcb);
	ATOM_I2C_ID_CONFIG_ACCESS *config;
	ATOM_I2C_RECORD record;

	if (!info)
		return BP_RESULT_BADINPUT;

	config = (ATOM_I2C_ID_CONFIG_ACCESS *) &i2c_channel_id;

	record.sucI2cId.bfHW_Capable = config->sbfAccess.bfHW_Capable;
	record.sucI2cId.bfI2C_LineMux = config->sbfAccess.bfI2C_LineMux;
	record.sucI2cId.bfHW_EngineID = config->sbfAccess.bfHW_EngineID;

	return get_gpio_i2c_info(bp, &record, info);
}