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
struct TYPE_4__ {int /*<<< orphan*/  sleep_cmd; int /*<<< orphan*/  sleep_cmd_next; } ;
struct TYPE_3__ {scalar_t__ state; } ;
struct iwl_priv {TYPE_2__ power_data; TYPE_1__ chain_noise_data; int /*<<< orphan*/  status; int /*<<< orphan*/  mutex; } ;
struct iwl_powertable_cmd {int flags; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ IWL_CHAIN_NOISE_ALIVE ; 
 scalar_t__ IWL_CHAIN_NOISE_DONE ; 
 int /*<<< orphan*/  IWL_DEBUG_INFO (struct iwl_priv*,char*) ; 
 int /*<<< orphan*/  IWL_DEBUG_POWER (struct iwl_priv*,char*,scalar_t__) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_priv*,char*,int) ; 
 int IWL_POWER_DRIVER_ALLOW_SLEEP_MSK ; 
 int /*<<< orphan*/  STATUS_SCANNING ; 
 int /*<<< orphan*/  iwl_dvm_set_pmi (struct iwl_priv*,int) ; 
 int /*<<< orphan*/  iwl_is_ready_rf (struct iwl_priv*) ; 
 int iwl_set_power (struct iwl_priv*,struct iwl_powertable_cmd*) ; 
 int /*<<< orphan*/  iwl_update_chain_flags (struct iwl_priv*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,struct iwl_powertable_cmd*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct iwl_powertable_cmd*,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int iwl_power_set_mode(struct iwl_priv *priv, struct iwl_powertable_cmd *cmd,
		       bool force)
{
	int ret;
	bool update_chains;

	lockdep_assert_held(&priv->mutex);

	/* Don't update the RX chain when chain noise calibration is running */
	update_chains = priv->chain_noise_data.state == IWL_CHAIN_NOISE_DONE ||
			priv->chain_noise_data.state == IWL_CHAIN_NOISE_ALIVE;

	if (!memcmp(&priv->power_data.sleep_cmd, cmd, sizeof(*cmd)) && !force)
		return 0;

	if (!iwl_is_ready_rf(priv))
		return -EIO;

	/* scan complete use sleep_power_next, need to be updated */
	memcpy(&priv->power_data.sleep_cmd_next, cmd, sizeof(*cmd));
	if (test_bit(STATUS_SCANNING, &priv->status) && !force) {
		IWL_DEBUG_INFO(priv, "Defer power set mode while scanning\n");
		return 0;
	}

	if (cmd->flags & IWL_POWER_DRIVER_ALLOW_SLEEP_MSK)
		iwl_dvm_set_pmi(priv, true);

	ret = iwl_set_power(priv, cmd);
	if (!ret) {
		if (!(cmd->flags & IWL_POWER_DRIVER_ALLOW_SLEEP_MSK))
			iwl_dvm_set_pmi(priv, false);

		if (update_chains)
			iwl_update_chain_flags(priv);
		else
			IWL_DEBUG_POWER(priv,
					"Cannot update the power, chain noise "
					"calibration running: %d\n",
					priv->chain_noise_data.state);

		memcpy(&priv->power_data.sleep_cmd, cmd, sizeof(*cmd));
	} else
		IWL_ERR(priv, "set power fail, ret = %d\n", ret);

	return ret;
}