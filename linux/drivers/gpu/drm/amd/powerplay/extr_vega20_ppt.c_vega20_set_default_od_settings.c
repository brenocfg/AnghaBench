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
struct smu_table_context {scalar_t__ overdrive_table; } ;
struct smu_context {struct smu_table_context smu_table; } ;
typedef  int /*<<< orphan*/  OverDriveTable_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SMU_TABLE_OVERDRIVE ; 
 scalar_t__ kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int smu_update_table (struct smu_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int vega20_set_default_od8_setttings (struct smu_context*) ; 

__attribute__((used)) static int vega20_set_default_od_settings(struct smu_context *smu,
					  bool initialize)
{
	struct smu_table_context *table_context = &smu->smu_table;
	int ret;

	if (initialize) {
		if (table_context->overdrive_table)
			return -EINVAL;

		table_context->overdrive_table = kzalloc(sizeof(OverDriveTable_t), GFP_KERNEL);

		if (!table_context->overdrive_table)
			return -ENOMEM;

		ret = smu_update_table(smu, SMU_TABLE_OVERDRIVE, 0,
				       table_context->overdrive_table, false);
		if (ret) {
			pr_err("Failed to export over drive table!\n");
			return ret;
		}

		ret = vega20_set_default_od8_setttings(smu);
		if (ret)
			return ret;
	}

	ret = smu_update_table(smu, SMU_TABLE_OVERDRIVE, 0,
			       table_context->overdrive_table, true);
	if (ret) {
		pr_err("Failed to import over drive table!\n");
		return ret;
	}

	return 0;
}