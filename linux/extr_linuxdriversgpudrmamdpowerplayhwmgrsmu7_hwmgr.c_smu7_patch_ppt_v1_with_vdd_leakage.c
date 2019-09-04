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
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct smu7_leakage_voltage {size_t count; int /*<<< orphan*/ * actual_voltage; int /*<<< orphan*/ * leakage_id; } ;
struct pp_hwmgr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATOM_VIRTUAL_VOLTAGE_ID0 ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static void smu7_patch_ppt_v1_with_vdd_leakage(struct pp_hwmgr *hwmgr,
		uint16_t *voltage, struct smu7_leakage_voltage *leakage_table)
{
	uint32_t index;

	/* search for leakage voltage ID 0xff01 ~ 0xff08 */
	for (index = 0; index < leakage_table->count; index++) {
		/* if this voltage matches a leakage voltage ID */
		/* patch with actual leakage voltage */
		if (leakage_table->leakage_id[index] == *voltage) {
			*voltage = leakage_table->actual_voltage[index];
			break;
		}
	}

	if (*voltage > ATOM_VIRTUAL_VOLTAGE_ID0)
		pr_err("Voltage value looks like a Leakage ID but it's not patched \n");
}