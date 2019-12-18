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
struct iwl_tt_mgmt {scalar_t__ state; } ;
struct iwl_priv {struct iwl_tt_mgmt thermal_throttle; } ;

/* Variables and functions */
 scalar_t__ IWL_TI_1 ; 

bool iwl_tt_is_low_power_state(struct iwl_priv *priv)
{
	struct iwl_tt_mgmt *tt = &priv->thermal_throttle;

	if (tt->state >= IWL_TI_1)
		return true;
	return false;
}