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
struct iwl_cfg {scalar_t__ nvm_type; } ;
typedef  int /*<<< orphan*/  __le32 ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 scalar_t__ IWL_NVM_EXT ; 
 int N_HW_ADDRS ; 
 int N_HW_ADDRS_FAMILY_8000 ; 
 int N_HW_ADDR_MASK ; 
 int le16_to_cpup (int /*<<< orphan*/  const*) ; 
 int le32_to_cpup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iwl_get_n_hw_addrs(const struct iwl_cfg *cfg, const __le16 *nvm_sw)
{
	int n_hw_addr;

	if (cfg->nvm_type != IWL_NVM_EXT)
		return le16_to_cpup(nvm_sw + N_HW_ADDRS);

	n_hw_addr = le32_to_cpup((__le32 *)(nvm_sw + N_HW_ADDRS_FAMILY_8000));

	return n_hw_addr & N_HW_ADDR_MASK;
}