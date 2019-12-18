#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  sleep_cmd; int /*<<< orphan*/  sleep_cmd_next; } ;
struct TYPE_5__ {scalar_t__ state; } ;
struct il_priv {TYPE_3__ power_data; TYPE_2__ chain_noise_data; TYPE_1__* ops; int /*<<< orphan*/  status; int /*<<< orphan*/  mutex; } ;
struct il_powertable_cmd {int flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* update_chain_flags ) (struct il_priv*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  D_INFO (char*) ; 
 int /*<<< orphan*/  D_POWER (char*,scalar_t__) ; 
 int EIO ; 
 scalar_t__ IL_CHAIN_NOISE_ALIVE ; 
 scalar_t__ IL_CHAIN_NOISE_DONE ; 
 int /*<<< orphan*/  IL_ERR (char*,int) ; 
 int IL_POWER_DRIVER_ALLOW_SLEEP_MSK ; 
 int /*<<< orphan*/  S_POWER_PMI ; 
 int /*<<< orphan*/  S_SCANNING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  il_is_ready_rf (struct il_priv*) ; 
 int il_set_power (struct il_priv*,struct il_powertable_cmd*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,struct il_powertable_cmd*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct il_powertable_cmd*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct il_priv*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
il_power_set_mode(struct il_priv *il, struct il_powertable_cmd *cmd, bool force)
{
	int ret;
	bool update_chains;

	lockdep_assert_held(&il->mutex);

	/* Don't update the RX chain when chain noise calibration is running */
	update_chains = il->chain_noise_data.state == IL_CHAIN_NOISE_DONE ||
	    il->chain_noise_data.state == IL_CHAIN_NOISE_ALIVE;

	if (!memcmp(&il->power_data.sleep_cmd, cmd, sizeof(*cmd)) && !force)
		return 0;

	if (!il_is_ready_rf(il))
		return -EIO;

	/* scan complete use sleep_power_next, need to be updated */
	memcpy(&il->power_data.sleep_cmd_next, cmd, sizeof(*cmd));
	if (test_bit(S_SCANNING, &il->status) && !force) {
		D_INFO("Defer power set mode while scanning\n");
		return 0;
	}

	if (cmd->flags & IL_POWER_DRIVER_ALLOW_SLEEP_MSK)
		set_bit(S_POWER_PMI, &il->status);

	ret = il_set_power(il, cmd);
	if (!ret) {
		if (!(cmd->flags & IL_POWER_DRIVER_ALLOW_SLEEP_MSK))
			clear_bit(S_POWER_PMI, &il->status);

		if (il->ops->update_chain_flags && update_chains)
			il->ops->update_chain_flags(il);
		else if (il->ops->update_chain_flags)
			D_POWER("Cannot update the power, chain noise "
				"calibration running: %d\n",
				il->chain_noise_data.state);

		memcpy(&il->power_data.sleep_cmd, cmd, sizeof(*cmd));
	} else
		IL_ERR("set power fail, ret = %d", ret);

	return ret;
}