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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct i40e_hw {int dummy; } ;
struct i40evf_adapter {int rss_key_size; int rss_lut_size; scalar_t__ rss_lut; scalar_t__ rss_key; struct i40e_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_VFQF_HKEY (int) ; 
 int /*<<< orphan*/  I40E_VFQF_HLUT (int) ; 
 int /*<<< orphan*/  i40e_flush (struct i40e_hw*) ; 
 int /*<<< orphan*/  wr32 (struct i40e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i40evf_config_rss_reg(struct i40evf_adapter *adapter)
{
	struct i40e_hw *hw = &adapter->hw;
	u32 *dw;
	u16 i;

	dw = (u32 *)adapter->rss_key;
	for (i = 0; i <= adapter->rss_key_size / 4; i++)
		wr32(hw, I40E_VFQF_HKEY(i), dw[i]);

	dw = (u32 *)adapter->rss_lut;
	for (i = 0; i <= adapter->rss_lut_size / 4; i++)
		wr32(hw, I40E_VFQF_HLUT(i), dw[i]);

	i40e_flush(hw);

	return 0;
}