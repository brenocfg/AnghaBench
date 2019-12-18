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
typedef  int u8 ;
struct iwl_mvm {TYPE_2__* cfg; TYPE_1__* fw; } ;
struct TYPE_4__ {int non_shared_ant; } ;
struct TYPE_3__ {int /*<<< orphan*/  ucode_capa; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_UCODE_TLV_CAPA_COEX_SCHEMA_2 ; 
 int first_antenna (int) ; 
 scalar_t__ fw_has_capa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

u8 iwl_mvm_bt_coex_get_single_ant_msk(struct iwl_mvm *mvm, u8 enabled_ants)
{
	if (fw_has_capa(&mvm->fw->ucode_capa, IWL_UCODE_TLV_CAPA_COEX_SCHEMA_2) &&
	    (mvm->cfg->non_shared_ant & enabled_ants))
		return mvm->cfg->non_shared_ant;

	return first_antenna(enabled_ants);
}