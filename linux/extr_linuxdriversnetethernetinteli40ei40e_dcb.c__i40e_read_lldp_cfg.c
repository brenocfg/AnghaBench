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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct i40e_lldp_variables {int dummy; } ;
struct i40e_hw {int dummy; } ;
typedef  int /*<<< orphan*/  raw_mem ;
typedef  scalar_t__ i40e_status ;
typedef  struct i40e_lldp_variables __le16 ;

/* Variables and functions */
 int I40E_PTR_TYPE ; 
 int /*<<< orphan*/  I40E_RESOURCE_READ ; 
 scalar_t__ i40e_acquire_nvm (struct i40e_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ i40e_aq_read_nvm (struct i40e_hw*,int,int,int,struct i40e_lldp_variables*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40e_release_nvm (struct i40e_hw*) ; 
 int le16_to_cpu (struct i40e_lldp_variables) ; 

__attribute__((used)) static i40e_status _i40e_read_lldp_cfg(struct i40e_hw *hw,
				       struct i40e_lldp_variables *lldp_cfg,
				       u8 module, u32 word_offset)
{
	u32 address, offset = (2 * word_offset);
	i40e_status ret;
	__le16 raw_mem;
	u16 mem;

	ret = i40e_acquire_nvm(hw, I40E_RESOURCE_READ);
	if (ret)
		return ret;

	ret = i40e_aq_read_nvm(hw, 0x0, module * 2, sizeof(raw_mem), &raw_mem,
			       true, NULL);
	i40e_release_nvm(hw);
	if (ret)
		return ret;

	mem = le16_to_cpu(raw_mem);
	/* Check if this pointer needs to be read in word size or 4K sector
	 * units.
	 */
	if (mem & I40E_PTR_TYPE)
		address = (0x7FFF & mem) * 4096;
	else
		address = (0x7FFF & mem) * 2;

	ret = i40e_acquire_nvm(hw, I40E_RESOURCE_READ);
	if (ret)
		goto err_lldp_cfg;

	ret = i40e_aq_read_nvm(hw, module, offset, sizeof(raw_mem), &raw_mem,
			       true, NULL);
	i40e_release_nvm(hw);
	if (ret)
		return ret;

	mem = le16_to_cpu(raw_mem);
	offset = mem + word_offset;
	offset *= 2;

	ret = i40e_acquire_nvm(hw, I40E_RESOURCE_READ);
	if (ret)
		goto err_lldp_cfg;

	ret = i40e_aq_read_nvm(hw, 0, address + offset,
			       sizeof(struct i40e_lldp_variables), lldp_cfg,
			       true, NULL);
	i40e_release_nvm(hw);

err_lldp_cfg:
	return ret;
}