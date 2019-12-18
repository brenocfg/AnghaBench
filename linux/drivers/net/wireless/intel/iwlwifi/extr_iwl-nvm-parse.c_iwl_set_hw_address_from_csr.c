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
struct iwl_trans {TYPE_1__* trans_cfg; } ;
struct iwl_nvm_data {int /*<<< orphan*/  hw_addr; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_4__ {int /*<<< orphan*/  mac_addr1_otp; int /*<<< orphan*/  mac_addr0_otp; int /*<<< orphan*/  mac_addr1_strap; int /*<<< orphan*/  mac_addr0_strap; } ;
struct TYPE_3__ {TYPE_2__* csr; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 scalar_t__ is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_flip_hw_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_read32 (struct iwl_trans*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iwl_set_hw_address_from_csr(struct iwl_trans *trans,
					struct iwl_nvm_data *data)
{
	__le32 mac_addr0 =
		cpu_to_le32(iwl_read32(trans,
				       trans->trans_cfg->csr->mac_addr0_strap));
	__le32 mac_addr1 =
		cpu_to_le32(iwl_read32(trans,
				       trans->trans_cfg->csr->mac_addr1_strap));

	iwl_flip_hw_address(mac_addr0, mac_addr1, data->hw_addr);
	/*
	 * If the OEM fused a valid address, use it instead of the one in the
	 * OTP
	 */
	if (is_valid_ether_addr(data->hw_addr))
		return;

	mac_addr0 = cpu_to_le32(iwl_read32(trans,
					trans->trans_cfg->csr->mac_addr0_otp));
	mac_addr1 = cpu_to_le32(iwl_read32(trans,
					trans->trans_cfg->csr->mac_addr1_otp));

	iwl_flip_hw_address(mac_addr0, mac_addr1, data->hw_addr);
}