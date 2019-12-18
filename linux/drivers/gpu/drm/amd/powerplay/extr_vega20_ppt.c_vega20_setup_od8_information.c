#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct vega20_od8_settings {int /*<<< orphan*/ * od_settings_max; int /*<<< orphan*/ * od_feature_capabilities; void* od_settings_min; } ;
struct smu_table_context {TYPE_2__* power_play_table; } ;
struct smu_context {scalar_t__ od_settings; struct smu_table_context smu_table; } ;
struct TYPE_3__ {int ucODTableRevision; int /*<<< orphan*/  ODSettingsMin; int /*<<< orphan*/  ODSettingsMax; int /*<<< orphan*/  ODSettingCount; int /*<<< orphan*/  ODFeatureCapabilities; int /*<<< orphan*/  ODFeatureCount; } ;
struct TYPE_4__ {TYPE_1__ OverDrive8Table; } ;
typedef  TYPE_2__ ATOM_Vega20_POWERPLAYTABLE ;

/* Variables and functions */
 scalar_t__ ATOM_VEGA20_ODFEATURE_COUNT ; 
 scalar_t__ ATOM_VEGA20_ODSETTING_COUNT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 void* kmemdup (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vega20_setup_od8_information(struct smu_context *smu)
{
	ATOM_Vega20_POWERPLAYTABLE *powerplay_table = NULL;
	struct smu_table_context *table_context = &smu->smu_table;
	struct vega20_od8_settings *od8_settings = (struct vega20_od8_settings *)smu->od_settings;

	uint32_t od_feature_count, od_feature_array_size,
		 od_setting_count, od_setting_array_size;

	if (!table_context->power_play_table)
		return -EINVAL;

	powerplay_table = table_context->power_play_table;

	if (powerplay_table->OverDrive8Table.ucODTableRevision == 1) {
		/* Setup correct ODFeatureCount, and store ODFeatureArray from
		 * powerplay table to od_feature_capabilities */
		od_feature_count =
			(le32_to_cpu(powerplay_table->OverDrive8Table.ODFeatureCount) >
			 ATOM_VEGA20_ODFEATURE_COUNT) ?
			ATOM_VEGA20_ODFEATURE_COUNT :
			le32_to_cpu(powerplay_table->OverDrive8Table.ODFeatureCount);

		od_feature_array_size = sizeof(uint8_t) * od_feature_count;

		if (od8_settings->od_feature_capabilities)
			return -EINVAL;

		od8_settings->od_feature_capabilities = kmemdup(&powerplay_table->OverDrive8Table.ODFeatureCapabilities,
								 od_feature_array_size,
								 GFP_KERNEL);
		if (!od8_settings->od_feature_capabilities)
			return -ENOMEM;

		/* Setup correct ODSettingCount, and store ODSettingArray from
		 * powerplay table to od_settings_max and od_setting_min */
		od_setting_count =
			(le32_to_cpu(powerplay_table->OverDrive8Table.ODSettingCount) >
			 ATOM_VEGA20_ODSETTING_COUNT) ?
			ATOM_VEGA20_ODSETTING_COUNT :
			le32_to_cpu(powerplay_table->OverDrive8Table.ODSettingCount);

		od_setting_array_size = sizeof(uint32_t) * od_setting_count;

		if (od8_settings->od_settings_max)
			return -EINVAL;

		od8_settings->od_settings_max = kmemdup(&powerplay_table->OverDrive8Table.ODSettingsMax,
							 od_setting_array_size,
							 GFP_KERNEL);

		if (!od8_settings->od_settings_max) {
			kfree(od8_settings->od_feature_capabilities);
			od8_settings->od_feature_capabilities = NULL;
			return -ENOMEM;
		}

		if (od8_settings->od_settings_min)
			return -EINVAL;

		od8_settings->od_settings_min = kmemdup(&powerplay_table->OverDrive8Table.ODSettingsMin,
							 od_setting_array_size,
							 GFP_KERNEL);

		if (!od8_settings->od_settings_min) {
			kfree(od8_settings->od_feature_capabilities);
			od8_settings->od_feature_capabilities = NULL;
			kfree(od8_settings->od_settings_max);
			od8_settings->od_settings_max = NULL;
			return -ENOMEM;
		}
	}

	return 0;
}