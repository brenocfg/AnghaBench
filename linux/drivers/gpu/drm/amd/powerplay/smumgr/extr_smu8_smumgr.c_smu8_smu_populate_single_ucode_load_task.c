#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_4__ {scalar_t__ kaddr; } ;
struct smu8_smumgr {size_t driver_buffer_length; TYPE_3__* driver_buffer; int /*<<< orphan*/  toc_entry_used_count; TYPE_1__ toc_buffer; } ;
struct pp_hwmgr {struct smu8_smumgr* smu_backend; } ;
struct TOC {struct SMU_Task* tasks; } ;
struct TYPE_5__ {int /*<<< orphan*/  high; int /*<<< orphan*/  low; } ;
struct SMU_Task {int /*<<< orphan*/  size_bytes; TYPE_2__ addr; int /*<<< orphan*/  next; int /*<<< orphan*/  arg; int /*<<< orphan*/  type; } ;
typedef  enum smu8_scratch_entry { ____Placeholder_smu8_scratch_entry } smu8_scratch_entry ;
struct TYPE_6__ {int firmware_ID; int /*<<< orphan*/  data_size; int /*<<< orphan*/  mc_addr; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  END_OF_TASK_LIST ; 
 int /*<<< orphan*/  TASK_TYPE_UCODE_LOAD ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  smu8_translate_firmware_enum_to_arg (struct pp_hwmgr*,int) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smu8_smu_populate_single_ucode_load_task(
					struct pp_hwmgr *hwmgr,
					enum smu8_scratch_entry fw_enum,
					bool is_last)
{
	uint8_t i;
	struct smu8_smumgr *smu8_smu = hwmgr->smu_backend;
	struct TOC *toc = (struct TOC *)smu8_smu->toc_buffer.kaddr;
	struct SMU_Task *task = &toc->tasks[smu8_smu->toc_entry_used_count++];

	task->type = TASK_TYPE_UCODE_LOAD;
	task->arg = smu8_translate_firmware_enum_to_arg(hwmgr, fw_enum);
	task->next = is_last ? END_OF_TASK_LIST : smu8_smu->toc_entry_used_count;

	for (i = 0; i < smu8_smu->driver_buffer_length; i++)
		if (smu8_smu->driver_buffer[i].firmware_ID == fw_enum)
			break;

	if (i >= smu8_smu->driver_buffer_length) {
		pr_err("Invalid Firmware Type\n");
		return -EINVAL;
	}

	task->addr.low = lower_32_bits(smu8_smu->driver_buffer[i].mc_addr);
	task->addr.high = upper_32_bits(smu8_smu->driver_buffer[i].mc_addr);
	task->size_bytes = smu8_smu->driver_buffer[i].data_size;

	return 0;
}