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
struct iwl_priv {int dummy; } ;
struct iwl_powertable_cmd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  iwl_power_build_cmd (struct iwl_priv*,struct iwl_powertable_cmd*) ; 
 int iwl_power_set_mode (struct iwl_priv*,struct iwl_powertable_cmd*,int) ; 

int iwl_power_update_mode(struct iwl_priv *priv, bool force)
{
	struct iwl_powertable_cmd cmd;

	iwl_power_build_cmd(priv, &cmd);
	return iwl_power_set_mode(priv, &cmd, force);
}