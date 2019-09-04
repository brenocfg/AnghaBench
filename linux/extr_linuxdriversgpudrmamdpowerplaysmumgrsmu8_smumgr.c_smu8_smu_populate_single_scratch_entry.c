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
typedef  int uint32_t ;
struct TYPE_2__ {int mc_addr; scalar_t__ kaddr; } ;
struct smu8_smumgr {int smu_buffer_used_bytes; TYPE_1__ smu_buffer; } ;
struct smu8_buffer_entry {int data_size; char* kaddr; int mc_addr; int firmware_ID; } ;
struct pp_hwmgr {struct smu8_smumgr* smu_backend; } ;
typedef  enum smu8_scratch_entry { ____Placeholder_smu8_scratch_entry } smu8_scratch_entry ;

/* Variables and functions */
 int SIZE_ALIGN_32 (int) ; 

__attribute__((used)) static int smu8_smu_populate_single_scratch_entry(
				struct pp_hwmgr *hwmgr,
				enum smu8_scratch_entry scratch_type,
				uint32_t ulsize_byte,
				struct smu8_buffer_entry *entry)
{
	struct smu8_smumgr *smu8_smu = hwmgr->smu_backend;
	uint32_t ulsize_aligned = SIZE_ALIGN_32(ulsize_byte);

	entry->data_size = ulsize_byte;
	entry->kaddr = (char *) smu8_smu->smu_buffer.kaddr +
				smu8_smu->smu_buffer_used_bytes;
	entry->mc_addr = smu8_smu->smu_buffer.mc_addr + smu8_smu->smu_buffer_used_bytes;
	entry->firmware_ID = scratch_type;

	smu8_smu->smu_buffer_used_bytes += ulsize_aligned;

	return 0;
}