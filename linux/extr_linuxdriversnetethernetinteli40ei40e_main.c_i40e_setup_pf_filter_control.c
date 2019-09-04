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
struct i40e_filter_control_settings {int enable_fdir; int enable_ethtype; int enable_macvlan; int /*<<< orphan*/  hash_lut_size; } ;
struct i40e_pf {int flags; int /*<<< orphan*/  hw; struct i40e_filter_control_settings filter_settings; } ;

/* Variables and functions */
 int ENOENT ; 
 int I40E_FLAG_FD_ATR_ENABLED ; 
 int I40E_FLAG_FD_SB_ENABLED ; 
 int /*<<< orphan*/  I40E_HASH_LUT_SIZE_128 ; 
 scalar_t__ i40e_set_filter_control (int /*<<< orphan*/ *,struct i40e_filter_control_settings*) ; 

__attribute__((used)) static int i40e_setup_pf_filter_control(struct i40e_pf *pf)
{
	struct i40e_filter_control_settings *settings = &pf->filter_settings;

	settings->hash_lut_size = I40E_HASH_LUT_SIZE_128;

	/* Flow Director is enabled */
	if (pf->flags & (I40E_FLAG_FD_SB_ENABLED | I40E_FLAG_FD_ATR_ENABLED))
		settings->enable_fdir = true;

	/* Ethtype and MACVLAN filters enabled for PF */
	settings->enable_ethtype = true;
	settings->enable_macvlan = true;

	if (i40e_set_filter_control(&pf->hw, settings))
		return -ENOENT;

	return 0;
}