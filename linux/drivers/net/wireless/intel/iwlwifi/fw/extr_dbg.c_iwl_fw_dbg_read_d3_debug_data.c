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
struct TYPE_3__ {int /*<<< orphan*/  d3_debug_data; } ;
struct iwl_fw_runtime {TYPE_1__ dump; TYPE_2__* trans; } ;
struct iwl_cfg {int /*<<< orphan*/  d3_debug_data_length; int /*<<< orphan*/  d3_debug_data_base_addr; } ;
struct TYPE_4__ {struct iwl_cfg* cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_fw_runtime*,char*) ; 
 int /*<<< orphan*/  iwl_fw_dbg_is_d3_debug_enabled (struct iwl_fw_runtime*) ; 
 int /*<<< orphan*/  iwl_trans_read_mem_bytes (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void iwl_fw_dbg_read_d3_debug_data(struct iwl_fw_runtime *fwrt)
{
	const struct iwl_cfg *cfg = fwrt->trans->cfg;

	if (!iwl_fw_dbg_is_d3_debug_enabled(fwrt))
		return;

	if (!fwrt->dump.d3_debug_data) {
		fwrt->dump.d3_debug_data = kmalloc(cfg->d3_debug_data_length,
						   GFP_KERNEL);
		if (!fwrt->dump.d3_debug_data) {
			IWL_ERR(fwrt,
				"failed to allocate memory for D3 debug data\n");
			return;
		}
	}

	/* if the buffer holds previous debug data it is overwritten */
	iwl_trans_read_mem_bytes(fwrt->trans, cfg->d3_debug_data_base_addr,
				 fwrt->dump.d3_debug_data,
				 cfg->d3_debug_data_length);
}