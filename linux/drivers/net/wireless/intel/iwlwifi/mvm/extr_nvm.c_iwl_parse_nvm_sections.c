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
struct iwl_nvm_section {scalar_t__ data; } ;
struct iwl_nvm_data {int dummy; } ;
struct iwl_mvm {TYPE_2__* fw; TYPE_5__* cfg; TYPE_4__* trans; struct iwl_nvm_section* nvm_sections; } ;
typedef  int /*<<< orphan*/  __le16 ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_10__ {size_t nvm_hw_section_num; } ;
struct TYPE_9__ {TYPE_1__* cfg; } ;
struct TYPE_8__ {int /*<<< orphan*/  lar_disable; } ;
struct TYPE_7__ {int /*<<< orphan*/  valid_rx_ant; int /*<<< orphan*/  valid_tx_ant; int /*<<< orphan*/  ucode_capa; } ;
struct TYPE_6__ {scalar_t__ nvm_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*) ; 
 scalar_t__ IWL_NVM_EXT ; 
 scalar_t__ IWL_NVM_SDP ; 
 int /*<<< orphan*/  IWL_UCODE_TLV_CAPA_LAR_SUPPORT ; 
 size_t NVM_SECTION_TYPE_CALIBRATION ; 
 size_t NVM_SECTION_TYPE_MAC_OVERRIDE ; 
 size_t NVM_SECTION_TYPE_PHY_SKU ; 
 size_t NVM_SECTION_TYPE_REGULATORY ; 
 size_t NVM_SECTION_TYPE_REGULATORY_SDP ; 
 size_t NVM_SECTION_TYPE_SW ; 
 scalar_t__ fw_has_capa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct iwl_nvm_data* iwl_parse_nvm_data (TYPE_4__*,TYPE_5__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_3__ iwlwifi_mod_params ; 

__attribute__((used)) static struct iwl_nvm_data *
iwl_parse_nvm_sections(struct iwl_mvm *mvm)
{
	struct iwl_nvm_section *sections = mvm->nvm_sections;
	const __be16 *hw;
	const __le16 *sw, *calib, *regulatory, *mac_override, *phy_sku;
	bool lar_enabled;
	int regulatory_type;

	/* Checking for required sections */
	if (mvm->trans->cfg->nvm_type != IWL_NVM_EXT) {
		if (!mvm->nvm_sections[NVM_SECTION_TYPE_SW].data ||
		    !mvm->nvm_sections[mvm->cfg->nvm_hw_section_num].data) {
			IWL_ERR(mvm, "Can't parse empty OTP/NVM sections\n");
			return NULL;
		}
	} else {
		if (mvm->trans->cfg->nvm_type == IWL_NVM_SDP)
			regulatory_type = NVM_SECTION_TYPE_REGULATORY_SDP;
		else
			regulatory_type = NVM_SECTION_TYPE_REGULATORY;

		/* SW and REGULATORY sections are mandatory */
		if (!mvm->nvm_sections[NVM_SECTION_TYPE_SW].data ||
		    !mvm->nvm_sections[regulatory_type].data) {
			IWL_ERR(mvm,
				"Can't parse empty family 8000 OTP/NVM sections\n");
			return NULL;
		}
		/* MAC_OVERRIDE or at least HW section must exist */
		if (!mvm->nvm_sections[mvm->cfg->nvm_hw_section_num].data &&
		    !mvm->nvm_sections[NVM_SECTION_TYPE_MAC_OVERRIDE].data) {
			IWL_ERR(mvm,
				"Can't parse mac_address, empty sections\n");
			return NULL;
		}

		/* PHY_SKU section is mandatory in B0 */
		if (!mvm->nvm_sections[NVM_SECTION_TYPE_PHY_SKU].data) {
			IWL_ERR(mvm,
				"Can't parse phy_sku in B0, empty sections\n");
			return NULL;
		}
	}

	hw = (const __be16 *)sections[mvm->cfg->nvm_hw_section_num].data;
	sw = (const __le16 *)sections[NVM_SECTION_TYPE_SW].data;
	calib = (const __le16 *)sections[NVM_SECTION_TYPE_CALIBRATION].data;
	mac_override =
		(const __le16 *)sections[NVM_SECTION_TYPE_MAC_OVERRIDE].data;
	phy_sku = (const __le16 *)sections[NVM_SECTION_TYPE_PHY_SKU].data;

	regulatory = mvm->trans->cfg->nvm_type == IWL_NVM_SDP ?
		(const __le16 *)sections[NVM_SECTION_TYPE_REGULATORY_SDP].data :
		(const __le16 *)sections[NVM_SECTION_TYPE_REGULATORY].data;

	lar_enabled = !iwlwifi_mod_params.lar_disable &&
		      fw_has_capa(&mvm->fw->ucode_capa,
				  IWL_UCODE_TLV_CAPA_LAR_SUPPORT);

	return iwl_parse_nvm_data(mvm->trans, mvm->cfg, hw, sw, calib,
				  regulatory, mac_override, phy_sku,
				  mvm->fw->valid_tx_ant, mvm->fw->valid_rx_ant,
				  lar_enabled);
}