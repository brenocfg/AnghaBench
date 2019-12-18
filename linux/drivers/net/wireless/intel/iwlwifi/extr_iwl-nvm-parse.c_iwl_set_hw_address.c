#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct iwl_trans {int dummy; } ;
struct iwl_nvm_data {int /*<<< orphan*/ * hw_addr; } ;
struct iwl_cfg {scalar_t__ nvm_type; scalar_t__ mac_addr_from_csr; } ;
typedef  int /*<<< orphan*/  __le16 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int EINVAL ; 
 int HW_ADDR ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_trans*,char*) ; 
 int /*<<< orphan*/  IWL_INFO (struct iwl_trans*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ IWL_NVM_EXT ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_set_hw_address_family_8000 (struct iwl_trans*,struct iwl_cfg const*,struct iwl_nvm_data*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  iwl_set_hw_address_from_csr (struct iwl_trans*,struct iwl_nvm_data*) ; 

__attribute__((used)) static int iwl_set_hw_address(struct iwl_trans *trans,
			      const struct iwl_cfg *cfg,
			      struct iwl_nvm_data *data, const __be16 *nvm_hw,
			      const __le16 *mac_override)
{
	if (cfg->mac_addr_from_csr) {
		iwl_set_hw_address_from_csr(trans, data);
	} else if (cfg->nvm_type != IWL_NVM_EXT) {
		const u8 *hw_addr = (const u8 *)(nvm_hw + HW_ADDR);

		/* The byte order is little endian 16 bit, meaning 214365 */
		data->hw_addr[0] = hw_addr[1];
		data->hw_addr[1] = hw_addr[0];
		data->hw_addr[2] = hw_addr[3];
		data->hw_addr[3] = hw_addr[2];
		data->hw_addr[4] = hw_addr[5];
		data->hw_addr[5] = hw_addr[4];
	} else {
		iwl_set_hw_address_family_8000(trans, cfg, data,
					       mac_override, nvm_hw);
	}

	if (!is_valid_ether_addr(data->hw_addr)) {
		IWL_ERR(trans, "no valid mac address was found\n");
		return -EINVAL;
	}

	IWL_INFO(trans, "base HW address: %pM\n", data->hw_addr);

	return 0;
}