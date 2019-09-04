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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_physical_address ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_freq_table ; 
 int /*<<< orphan*/  ti_tps68470_regmap_update_bits ; 
 int /*<<< orphan*/  tps68470_pmic_common_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tps68470_pmic_get_clk_freq ; 

__attribute__((used)) static acpi_status tps68470_pmic_cfreq_handler(u32 function,
					    acpi_physical_address address,
					    u32 bits, u64 *value,
					    void *handler_context,
					    void *region_context)
{
	return tps68470_pmic_common_handler(function, address, bits, value,
				region_context,
				tps68470_pmic_get_clk_freq,
				ti_tps68470_regmap_update_bits,
				clk_freq_table,
				ARRAY_SIZE(clk_freq_table));
}