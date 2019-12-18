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
struct iwl_priv {int /*<<< orphan*/  trans; int /*<<< orphan*/  mutex; int /*<<< orphan*/  ucode_loaded; int /*<<< orphan*/  status; } ;
struct iwl_host_cmd {int flags; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int CMD_ASYNC ; 
 int EIO ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_priv*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWL_WARN (struct iwl_priv*,char*,char*) ; 
 int /*<<< orphan*/  STATUS_FW_ERROR ; 
 int /*<<< orphan*/  iwl_get_cmd_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ iwl_is_ctkill (struct iwl_priv*) ; 
 scalar_t__ iwl_is_rfkill (struct iwl_priv*) ; 
 int iwl_trans_send_cmd (int /*<<< orphan*/ ,struct iwl_host_cmd*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int iwl_dvm_send_cmd(struct iwl_priv *priv, struct iwl_host_cmd *cmd)
{
	if (iwl_is_rfkill(priv) || iwl_is_ctkill(priv)) {
		IWL_WARN(priv, "Not sending command - %s KILL\n",
			 iwl_is_rfkill(priv) ? "RF" : "CT");
		return -EIO;
	}

	if (test_bit(STATUS_FW_ERROR, &priv->status)) {
		IWL_ERR(priv, "Command %s failed: FW Error\n",
			iwl_get_cmd_string(priv->trans, cmd->id));
		return -EIO;
	}

	/*
	 * This can happen upon FW ASSERT: we clear the STATUS_FW_ERROR flag
	 * in iwl_down but cancel the workers only later.
	 */
	if (!priv->ucode_loaded) {
		IWL_ERR(priv, "Fw not loaded - dropping CMD: %x\n", cmd->id);
		return -EIO;
	}

	/*
	 * Synchronous commands from this op-mode must hold
	 * the mutex, this ensures we don't try to send two
	 * (or more) synchronous commands at a time.
	 */
	if (!(cmd->flags & CMD_ASYNC))
		lockdep_assert_held(&priv->mutex);

	return iwl_trans_send_cmd(priv->trans, cmd);
}