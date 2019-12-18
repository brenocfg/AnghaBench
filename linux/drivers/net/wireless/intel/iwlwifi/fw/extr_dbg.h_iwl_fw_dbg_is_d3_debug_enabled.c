#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct iwl_fw_runtime {int /*<<< orphan*/  ops_ctx; TYPE_4__* ops; TYPE_3__* trans; TYPE_1__* fw; } ;
struct TYPE_8__ {scalar_t__ (* d3_debug_enable ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {TYPE_2__* cfg; } ;
struct TYPE_6__ {scalar_t__ d3_debug_data_length; } ;
struct TYPE_5__ {int /*<<< orphan*/  ucode_capa; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_FW_ERROR_DUMP_D3_DEBUG_DATA ; 
 int /*<<< orphan*/  IWL_UCODE_TLV_CAPA_D3_DEBUG ; 
 scalar_t__ fw_has_capa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ iwl_fw_dbg_type_on (struct iwl_fw_runtime*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool iwl_fw_dbg_is_d3_debug_enabled(struct iwl_fw_runtime *fwrt)
{
	return fw_has_capa(&fwrt->fw->ucode_capa,
			   IWL_UCODE_TLV_CAPA_D3_DEBUG) &&
		fwrt->trans->cfg->d3_debug_data_length && fwrt->ops &&
		fwrt->ops->d3_debug_enable &&
		fwrt->ops->d3_debug_enable(fwrt->ops_ctx) &&
		iwl_fw_dbg_type_on(fwrt, IWL_FW_ERROR_DUMP_D3_DEBUG_DATA);
}