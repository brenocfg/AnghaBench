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
typedef  int u32 ;
struct iwl_fw_runtime {int /*<<< orphan*/  trans; } ;
struct TYPE_2__ {int /*<<< orphan*/  range_data_size; } ;
struct iwl_fw_ini_region_cfg {TYPE_1__ internal; int /*<<< orphan*/  offset; int /*<<< orphan*/ * start_addr; } ;
struct iwl_fw_ini_error_dump_range {int /*<<< orphan*/  range_data_size; void* internal_base_addr; int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 void* cpu_to_le32 (int) ; 
 int iwl_trans_read32 (int /*<<< orphan*/ ,int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iwl_dump_ini_csr_iter(struct iwl_fw_runtime *fwrt,
				 struct iwl_fw_ini_region_cfg *reg,
				 void *range_ptr, int idx)
{
	struct iwl_fw_ini_error_dump_range *range = range_ptr;
	__le32 *val = range->data;
	u32 addr = le32_to_cpu(reg->start_addr[idx]) + le32_to_cpu(reg->offset);
	int i;

	range->internal_base_addr = cpu_to_le32(addr);
	range->range_data_size = reg->internal.range_data_size;
	for (i = 0; i < le32_to_cpu(reg->internal.range_data_size); i += 4)
		*val++ = cpu_to_le32(iwl_trans_read32(fwrt->trans, addr + i));

	return sizeof(*range) + le32_to_cpu(range->range_data_size);
}