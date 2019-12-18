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
struct i40e_virt_mem {scalar_t__ va; } ;
struct i40e_hw {int dummy; } ;
struct i40e_dcbx_config {int dummy; } ;
typedef  scalar_t__ i40e_status ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_LLDPDU_SIZE ; 
 scalar_t__ i40e_allocate_virt_mem (struct i40e_hw*,struct i40e_virt_mem*,int /*<<< orphan*/ ) ; 
 scalar_t__ i40e_aq_get_lldp_mib (struct i40e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40e_free_virt_mem (struct i40e_hw*,struct i40e_virt_mem*) ; 
 scalar_t__ i40e_lldp_to_dcb_config (int /*<<< orphan*/ *,struct i40e_dcbx_config*) ; 

i40e_status i40e_aq_get_dcb_config(struct i40e_hw *hw, u8 mib_type,
				   u8 bridgetype,
				   struct i40e_dcbx_config *dcbcfg)
{
	i40e_status ret = 0;
	struct i40e_virt_mem mem;
	u8 *lldpmib;

	/* Allocate the LLDPDU */
	ret = i40e_allocate_virt_mem(hw, &mem, I40E_LLDPDU_SIZE);
	if (ret)
		return ret;

	lldpmib = (u8 *)mem.va;
	ret = i40e_aq_get_lldp_mib(hw, bridgetype, mib_type,
				   (void *)lldpmib, I40E_LLDPDU_SIZE,
				   NULL, NULL, NULL);
	if (ret)
		goto free_mem;

	/* Parse LLDP MIB to get dcb configuration */
	ret = i40e_lldp_to_dcb_config(lldpmib, dcbcfg);

free_mem:
	i40e_free_virt_mem(hw, &mem);
	return ret;
}