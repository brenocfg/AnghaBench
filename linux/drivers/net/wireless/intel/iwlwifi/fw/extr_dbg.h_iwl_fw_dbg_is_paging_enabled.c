#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct iwl_fw_runtime {size_t cur_fw_img; TYPE_5__* fw_paging_db; TYPE_4__* fw; TYPE_2__* trans; } ;
struct TYPE_10__ {scalar_t__ fw_paging_block; } ;
struct TYPE_9__ {TYPE_3__* img; } ;
struct TYPE_8__ {scalar_t__ paging_mem_size; } ;
struct TYPE_7__ {TYPE_1__* trans_cfg; } ;
struct TYPE_6__ {int /*<<< orphan*/  gen2; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_FW_ERROR_DUMP_PAGING ; 
 size_t IWL_UCODE_TYPE_MAX ; 
 scalar_t__ iwl_fw_dbg_type_on (struct iwl_fw_runtime*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool iwl_fw_dbg_is_paging_enabled(struct iwl_fw_runtime *fwrt)
{
	return iwl_fw_dbg_type_on(fwrt, IWL_FW_ERROR_DUMP_PAGING) &&
		!fwrt->trans->trans_cfg->gen2 &&
		fwrt->cur_fw_img < IWL_UCODE_TYPE_MAX &&
		fwrt->fw->img[fwrt->cur_fw_img].paging_mem_size &&
		fwrt->fw_paging_db[0].fw_paging_block;
}