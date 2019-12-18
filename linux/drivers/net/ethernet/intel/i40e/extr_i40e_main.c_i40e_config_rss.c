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
typedef  int /*<<< orphan*/  u16 ;
struct i40e_vsi {struct i40e_pf* back; } ;
struct i40e_pf {int hw_features; } ;

/* Variables and functions */
 int I40E_HW_RSS_AQ_CAPABLE ; 
 int i40e_config_rss_aq (struct i40e_vsi*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int i40e_config_rss_reg (struct i40e_vsi*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int i40e_config_rss(struct i40e_vsi *vsi, u8 *seed, u8 *lut, u16 lut_size)
{
	struct i40e_pf *pf = vsi->back;

	if (pf->hw_features & I40E_HW_RSS_AQ_CAPABLE)
		return i40e_config_rss_aq(vsi, seed, lut, lut_size);
	else
		return i40e_config_rss_reg(vsi, seed, lut, lut_size);
}