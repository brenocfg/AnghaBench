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
struct iwl_mvm {TYPE_3__* cfg; TYPE_2__* fw; TYPE_1__* nvm_data; } ;
struct TYPE_8__ {scalar_t__ lar_disable; } ;
struct TYPE_7__ {scalar_t__ nvm_type; } ;
struct TYPE_6__ {int /*<<< orphan*/  ucode_capa; } ;
struct TYPE_5__ {int lar_enabled; } ;

/* Variables and functions */
 scalar_t__ IWL_NVM_EXT ; 
 int /*<<< orphan*/  IWL_UCODE_TLV_CAPA_LAR_SUPPORT ; 
 int fw_has_capa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_4__ iwlwifi_mod_params ; 

__attribute__((used)) static inline bool iwl_mvm_is_lar_supported(struct iwl_mvm *mvm)
{
	bool nvm_lar = mvm->nvm_data->lar_enabled;
	bool tlv_lar = fw_has_capa(&mvm->fw->ucode_capa,
				   IWL_UCODE_TLV_CAPA_LAR_SUPPORT);

	if (iwlwifi_mod_params.lar_disable)
		return false;

	/*
	 * Enable LAR only if it is supported by the FW (TLV) &&
	 * enabled in the NVM
	 */
	if (mvm->cfg->nvm_type == IWL_NVM_EXT)
		return nvm_lar && tlv_lar;
	else
		return tlv_lar;
}