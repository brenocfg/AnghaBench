#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct scatterlist {int dummy; } ;
struct TYPE_10__ {scalar_t__ monitor_only; } ;
struct iwl_fw_runtime {TYPE_7__* trans; TYPE_3__ dump; TYPE_2__* fw; } ;
struct iwl_fw_error_dump_file {int /*<<< orphan*/  file_len; } ;
struct iwl_fw_dump_ptrs {TYPE_4__* trans_ptr; TYPE_4__* fwrt_ptr; scalar_t__ fwrt_len; } ;
struct TYPE_12__ {int /*<<< orphan*/  dev; } ;
struct TYPE_11__ {scalar_t__ len; struct TYPE_11__* data; } ;
struct TYPE_8__ {scalar_t__ dump_mask; } ;
struct TYPE_9__ {TYPE_1__ dbg; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IWL_FW_ERROR_DUMP_FW_MONITOR ; 
 struct scatterlist* alloc_sgtable (scalar_t__) ; 
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__) ; 
 int /*<<< orphan*/  dev_coredumpsg (int /*<<< orphan*/ ,struct scatterlist*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct iwl_fw_error_dump_file* iwl_fw_error_dump_file (struct iwl_fw_runtime*,struct iwl_fw_dump_ptrs*) ; 
 int /*<<< orphan*/  iwl_fw_free_dump_desc (struct iwl_fw_runtime*) ; 
 TYPE_4__* iwl_trans_dump_data (TYPE_7__*,scalar_t__) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_nents (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_pcopy_from_buffer (struct scatterlist*,int /*<<< orphan*/ ,TYPE_4__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  vfree (TYPE_4__*) ; 

__attribute__((used)) static void iwl_fw_error_dump(struct iwl_fw_runtime *fwrt)
{
	struct iwl_fw_dump_ptrs fw_error_dump = {};
	struct iwl_fw_error_dump_file *dump_file;
	struct scatterlist *sg_dump_data;
	u32 file_len;
	u32 dump_mask = fwrt->fw->dbg.dump_mask;

	dump_file = iwl_fw_error_dump_file(fwrt, &fw_error_dump);
	if (!dump_file)
		goto out;

	if (fwrt->dump.monitor_only)
		dump_mask &= IWL_FW_ERROR_DUMP_FW_MONITOR;

	fw_error_dump.trans_ptr = iwl_trans_dump_data(fwrt->trans, dump_mask);
	file_len = le32_to_cpu(dump_file->file_len);
	fw_error_dump.fwrt_len = file_len;

	if (fw_error_dump.trans_ptr) {
		file_len += fw_error_dump.trans_ptr->len;
		dump_file->file_len = cpu_to_le32(file_len);
	}

	sg_dump_data = alloc_sgtable(file_len);
	if (sg_dump_data) {
		sg_pcopy_from_buffer(sg_dump_data,
				     sg_nents(sg_dump_data),
				     fw_error_dump.fwrt_ptr,
				     fw_error_dump.fwrt_len, 0);
		if (fw_error_dump.trans_ptr)
			sg_pcopy_from_buffer(sg_dump_data,
					     sg_nents(sg_dump_data),
					     fw_error_dump.trans_ptr->data,
					     fw_error_dump.trans_ptr->len,
					     fw_error_dump.fwrt_len);
		dev_coredumpsg(fwrt->trans->dev, sg_dump_data, file_len,
			       GFP_KERNEL);
	}
	vfree(fw_error_dump.fwrt_ptr);
	vfree(fw_error_dump.trans_ptr);

out:
	iwl_fw_free_dump_desc(fwrt);
}