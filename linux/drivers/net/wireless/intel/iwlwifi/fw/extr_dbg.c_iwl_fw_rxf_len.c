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
struct iwl_fwrt_shared_mem_cfg {int num_lmacs; TYPE_1__* lmac; int /*<<< orphan*/  rxfifo2_size; } ;
struct iwl_fw_runtime {int dummy; } ;
struct iwl_fw_error_dump_fifo {int dummy; } ;
struct iwl_fw_error_dump_data {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rxfifo1_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_LEN (int,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  IWL_FW_ERROR_DUMP_RXF ; 
 int MAX_NUM_LMAC ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  iwl_fw_dbg_type_on (struct iwl_fw_runtime*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iwl_fw_rxf_len(struct iwl_fw_runtime *fwrt,
			  struct iwl_fwrt_shared_mem_cfg *mem_cfg)
{
	size_t hdr_len = sizeof(struct iwl_fw_error_dump_data) +
			 sizeof(struct iwl_fw_error_dump_fifo);
	u32 fifo_len = 0;
	int i;

	if (!iwl_fw_dbg_type_on(fwrt, IWL_FW_ERROR_DUMP_RXF))
		return 0;

	/* Count RXF2 size */
	ADD_LEN(fifo_len, mem_cfg->rxfifo2_size, hdr_len);

	/* Count RXF1 sizes */
	if (WARN_ON(mem_cfg->num_lmacs > MAX_NUM_LMAC))
		mem_cfg->num_lmacs = MAX_NUM_LMAC;

	for (i = 0; i < mem_cfg->num_lmacs; i++)
		ADD_LEN(fifo_len, mem_cfg->lmac[i].rxfifo1_size, hdr_len);

	return fifo_len;
}