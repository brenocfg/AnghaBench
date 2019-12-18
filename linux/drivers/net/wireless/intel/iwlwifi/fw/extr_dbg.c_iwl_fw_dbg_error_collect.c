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
struct iwl_fw_runtime {TYPE_2__* trans; } ;
struct TYPE_3__ {int /*<<< orphan*/  type; } ;
struct iwl_fw_dump_desc {scalar_t__ len; TYPE_1__ trig_desc; } ;
typedef  enum iwl_fw_dbg_trigger { ____Placeholder_iwl_fw_dbg_trigger } iwl_fw_dbg_trigger ;
struct TYPE_4__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  STATUS_DEVICE_ENABLED ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int iwl_fw_dbg_collect_desc (struct iwl_fw_runtime*,struct iwl_fw_dump_desc*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_trans_sync_nmi (TYPE_2__*) ; 
 int /*<<< orphan*/  kfree (struct iwl_fw_dump_desc*) ; 
 struct iwl_fw_dump_desc* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int iwl_fw_dbg_error_collect(struct iwl_fw_runtime *fwrt,
			     enum iwl_fw_dbg_trigger trig_type)
{
	int ret;
	struct iwl_fw_dump_desc *iwl_dump_error_desc;

	if (!test_bit(STATUS_DEVICE_ENABLED, &fwrt->trans->status))
		return -EIO;

	iwl_dump_error_desc = kmalloc(sizeof(*iwl_dump_error_desc), GFP_KERNEL);
	if (!iwl_dump_error_desc)
		return -ENOMEM;

	iwl_dump_error_desc->trig_desc.type = cpu_to_le32(trig_type);
	iwl_dump_error_desc->len = 0;

	ret = iwl_fw_dbg_collect_desc(fwrt, iwl_dump_error_desc, false, 0);
	if (ret)
		kfree(iwl_dump_error_desc);
	else
		iwl_trans_sync_nmi(fwrt->trans);

	return ret;
}