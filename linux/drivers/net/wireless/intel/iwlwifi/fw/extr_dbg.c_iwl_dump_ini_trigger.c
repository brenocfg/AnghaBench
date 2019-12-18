#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct list_head {int dummy; } ;
struct TYPE_2__ {struct iwl_fw_ini_region_cfg** active_regs; } ;
struct iwl_fw_runtime {TYPE_1__ dump; } ;
struct iwl_fw_ini_trigger {int /*<<< orphan*/ * data; int /*<<< orphan*/  num_regions; } ;
struct iwl_fw_ini_region_cfg {int /*<<< orphan*/  region_type; int /*<<< orphan*/  domain; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct iwl_fw_ini_region_cfg**) ; 
 scalar_t__ IWL_FW_INI_DBG_DOMAIN_ALWAYS_ON ; 
 int /*<<< orphan*/  IWL_WARN (struct iwl_fw_runtime*,char*,size_t) ; 
 scalar_t__ WARN_ON (int) ; 
 size_t iwl_dump_ini_info (struct iwl_fw_runtime*,struct iwl_fw_ini_trigger*,struct list_head*) ; 
 size_t iwl_dump_ini_mem (struct iwl_fw_runtime*,struct list_head*,struct iwl_fw_ini_region_cfg*,struct iwl_fw_ini_region_cfg**) ; 
 struct iwl_fw_ini_region_cfg** iwl_dump_ini_region_ops ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 iwl_dump_ini_trigger(struct iwl_fw_runtime *fwrt,
				struct iwl_fw_ini_trigger *trigger,
				struct list_head *list)
{
	int i;
	u32 size = 0;

	for (i = 0; i < le32_to_cpu(trigger->num_regions); i++) {
		u32 reg_id = le32_to_cpu(trigger->data[i]), reg_type;
		struct iwl_fw_ini_region_cfg *reg;

		if (WARN_ON(reg_id >= ARRAY_SIZE(fwrt->dump.active_regs)))
			continue;

		reg = fwrt->dump.active_regs[reg_id];
		if (!reg) {
			IWL_WARN(fwrt,
				 "WRT: Unassigned region id %d, skipping\n",
				 reg_id);
			continue;
		}

		/* currently the driver supports always on domain only */
		if (le32_to_cpu(reg->domain) != IWL_FW_INI_DBG_DOMAIN_ALWAYS_ON)
			continue;

		reg_type = le32_to_cpu(reg->region_type);
		if (reg_type >= ARRAY_SIZE(iwl_dump_ini_region_ops))
			continue;

		size += iwl_dump_ini_mem(fwrt, list, reg,
					 &iwl_dump_ini_region_ops[reg_type]);
	}

	if (size)
		size += iwl_dump_ini_info(fwrt, trigger, list);

	return size;
}