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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct graphics_object_i2c_info {int dummy; } ;
struct dc_bios {int dummy; } ;
struct bios_parser {int /*<<< orphan*/  base; } ;
struct atom_data_revision {int major; int minor; int /*<<< orphan*/  member_0; } ;
struct atom_common_table_header {int dummy; } ;
typedef  enum bp_result { ____Placeholder_bp_result } bp_result ;

/* Variables and functions */
 struct bios_parser* BP_FROM_DCB (struct dc_bios*) ; 
 int BP_RESULT_NORECORD ; 
 int BP_RESULT_OK ; 
 int /*<<< orphan*/  DATA_TABLES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bios_get_image (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int bios_parser_get_thermal_ddc_info (struct dc_bios*,int /*<<< orphan*/ ,struct graphics_object_i2c_info*) ; 
 int /*<<< orphan*/  get_atom_data_table_revision (struct atom_common_table_header*,struct atom_data_revision*) ; 
 int get_voltage_ddc_info_v4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct atom_common_table_header*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  voltageobject_info ; 

__attribute__((used)) static enum bp_result bios_parser_get_voltage_ddc_info(struct dc_bios *dcb,
	uint32_t index,
	struct graphics_object_i2c_info *info)
{
	uint8_t i2c_line = 0;
	enum bp_result result = BP_RESULT_NORECORD;
	uint8_t *voltage_info_address;
	struct atom_common_table_header *header;
	struct atom_data_revision revision = {0};
	struct bios_parser *bp = BP_FROM_DCB(dcb);

	if (!DATA_TABLES(voltageobject_info))
		return result;

	voltage_info_address = bios_get_image(&bp->base,
			DATA_TABLES(voltageobject_info),
			sizeof(struct atom_common_table_header));

	header = (struct atom_common_table_header *) voltage_info_address;

	get_atom_data_table_revision(header, &revision);

	switch (revision.major) {
	case 4:
		if (revision.minor != 1)
			break;
		result = get_voltage_ddc_info_v4(&i2c_line, index, header,
			voltage_info_address);
		break;
	}

	if (result == BP_RESULT_OK)
		result = bios_parser_get_thermal_ddc_info(dcb,
			i2c_line, info);

	return result;
}