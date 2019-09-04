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
typedef  int u64 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_physical_address ;

/* Variables and functions */
 int ACPI_WRITE ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  power_table ; 
 int /*<<< orphan*/  ti_tps68470_regmap_update_bits ; 
 int /*<<< orphan*/  tps68470_pmic_common_handler (int,int /*<<< orphan*/ ,int,int*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tps68470_pmic_get_power ; 

__attribute__((used)) static acpi_status tps68470_pmic_pwr_handler(u32 function,
					 acpi_physical_address address,
					 u32 bits, u64 *value,
					 void *handler_context,
					 void *region_context)
{
	if (bits != 32)
		return AE_BAD_PARAMETER;

	/* set/clear for bit 0, bits 0 and 1 together */
	if (function == ACPI_WRITE &&
	    !(*value == 0 || *value == 1 || *value == 3)) {
		return AE_BAD_PARAMETER;
	}

	return tps68470_pmic_common_handler(function, address, bits, value,
				region_context,
				tps68470_pmic_get_power,
				ti_tps68470_regmap_update_bits,
				power_table,
				ARRAY_SIZE(power_table));
}