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
struct smu_table_context {int /*<<< orphan*/  overdrive_table; } ;
struct smu_context {struct smu_table_context smu_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMU_TABLE_OVERDRIVE ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int smu_update_table (struct smu_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int vega20_update_specified_od8_value (struct smu_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vega20_update_od8_settings(struct smu_context *smu,
				      uint32_t index,
				      uint32_t value)
{
	struct smu_table_context *table_context = &smu->smu_table;
	int ret;

	ret = smu_update_table(smu, SMU_TABLE_OVERDRIVE, 0,
			       table_context->overdrive_table, false);
	if (ret) {
		pr_err("Failed to export over drive table!\n");
		return ret;
	}

	ret = vega20_update_specified_od8_value(smu, index, value);
	if (ret)
		return ret;

	ret = smu_update_table(smu, SMU_TABLE_OVERDRIVE, 0,
			       table_context->overdrive_table, true);
	if (ret) {
		pr_err("Failed to import over drive table!\n");
		return ret;
	}

	return 0;
}