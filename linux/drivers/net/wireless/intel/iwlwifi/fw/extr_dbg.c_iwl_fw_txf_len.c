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
typedef  int u32 ;
struct iwl_fwrt_shared_mem_cfg {int num_lmacs; int num_txfifo_entries; int /*<<< orphan*/ * internal_txfifo_size; TYPE_1__* lmac; } ;
struct iwl_fw_runtime {TYPE_2__* fw; } ;
struct iwl_fw_error_dump_fifo {int dummy; } ;
struct iwl_fw_error_dump_data {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  ucode_capa; } ;
struct TYPE_3__ {int /*<<< orphan*/ * txfifo_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_LEN (int,int /*<<< orphan*/ ,size_t) ; 
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWL_FW_ERROR_DUMP_INTERNAL_TXF ; 
 int /*<<< orphan*/  IWL_FW_ERROR_DUMP_TXF ; 
 int /*<<< orphan*/  IWL_UCODE_TLV_CAPA_EXTEND_SHARED_MEM_CFG ; 
 int MAX_NUM_LMAC ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ fw_has_capa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ iwl_fw_dbg_type_on (struct iwl_fw_runtime*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iwl_fw_txf_len(struct iwl_fw_runtime *fwrt,
			  struct iwl_fwrt_shared_mem_cfg *mem_cfg)
{
	size_t hdr_len = sizeof(struct iwl_fw_error_dump_data) +
			 sizeof(struct iwl_fw_error_dump_fifo);
	u32 fifo_len = 0;
	int i;

	if (!iwl_fw_dbg_type_on(fwrt, IWL_FW_ERROR_DUMP_TXF))
		goto dump_internal_txf;

	/* Count TXF sizes */
	if (WARN_ON(mem_cfg->num_lmacs > MAX_NUM_LMAC))
		mem_cfg->num_lmacs = MAX_NUM_LMAC;

	for (i = 0; i < mem_cfg->num_lmacs; i++) {
		int j;

		for (j = 0; j < mem_cfg->num_txfifo_entries; j++)
			ADD_LEN(fifo_len, mem_cfg->lmac[i].txfifo_size[j],
				hdr_len);
	}

dump_internal_txf:
	if (!(iwl_fw_dbg_type_on(fwrt, IWL_FW_ERROR_DUMP_INTERNAL_TXF) &&
	      fw_has_capa(&fwrt->fw->ucode_capa,
			  IWL_UCODE_TLV_CAPA_EXTEND_SHARED_MEM_CFG)))
		goto out;

	for (i = 0; i < ARRAY_SIZE(mem_cfg->internal_txfifo_size); i++)
		ADD_LEN(fifo_len, mem_cfg->internal_txfifo_size[i], hdr_len);

out:
	return fifo_len;
}