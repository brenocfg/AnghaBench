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
typedef  int /*<<< orphan*/  u16 ;
struct iwl_priv {int cur_ucode; int ucode_loaded; int /*<<< orphan*/  notif_wait; int /*<<< orphan*/  trans; int /*<<< orphan*/  fw; } ;
struct iwl_notification_wait {int dummy; } ;
struct iwl_alive_data {int /*<<< orphan*/  valid; } ;
struct fw_img {int dummy; } ;
typedef  enum iwl_ucode_type { ____Placeholder_iwl_ucode_type } iwl_ucode_type ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/  const*) ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_priv*,char*) ; 
 int IWL_UCODE_WOWLAN ; 
 int /*<<< orphan*/  IWL_WARN (struct iwl_priv*,char*,int) ; 
#define  REPLY_ALIVE 128 
 int /*<<< orphan*/  UCODE_ALIVE_TIMEOUT ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  iwl_alive_fn ; 
 int iwl_alive_notify (struct iwl_priv*) ; 
 struct fw_img* iwl_get_ucode_image (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iwl_init_notification_wait (int /*<<< orphan*/ *,struct iwl_notification_wait*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iwl_alive_data*) ; 
 int /*<<< orphan*/  iwl_remove_notification (int /*<<< orphan*/ *,struct iwl_notification_wait*) ; 
 int iwl_trans_start_fw (int /*<<< orphan*/ ,struct fw_img const*,int) ; 
 int iwl_wait_notification (int /*<<< orphan*/ *,struct iwl_notification_wait*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 

int iwl_load_ucode_wait_alive(struct iwl_priv *priv,
				 enum iwl_ucode_type ucode_type)
{
	struct iwl_notification_wait alive_wait;
	struct iwl_alive_data alive_data;
	const struct fw_img *fw;
	int ret;
	enum iwl_ucode_type old_type;
	static const u16 alive_cmd[] = { REPLY_ALIVE };

	fw = iwl_get_ucode_image(priv->fw, ucode_type);
	if (WARN_ON(!fw))
		return -EINVAL;

	old_type = priv->cur_ucode;
	priv->cur_ucode = ucode_type;
	priv->ucode_loaded = false;

	iwl_init_notification_wait(&priv->notif_wait, &alive_wait,
				   alive_cmd, ARRAY_SIZE(alive_cmd),
				   iwl_alive_fn, &alive_data);

	ret = iwl_trans_start_fw(priv->trans, fw, false);
	if (ret) {
		priv->cur_ucode = old_type;
		iwl_remove_notification(&priv->notif_wait, &alive_wait);
		return ret;
	}

	/*
	 * Some things may run in the background now, but we
	 * just wait for the ALIVE notification here.
	 */
	ret = iwl_wait_notification(&priv->notif_wait, &alive_wait,
					UCODE_ALIVE_TIMEOUT);
	if (ret) {
		priv->cur_ucode = old_type;
		return ret;
	}

	if (!alive_data.valid) {
		IWL_ERR(priv, "Loaded ucode is not valid!\n");
		priv->cur_ucode = old_type;
		return -EIO;
	}

	priv->ucode_loaded = true;

	if (ucode_type != IWL_UCODE_WOWLAN) {
		/* delay a bit to give rfkill time to run */
		msleep(5);
	}

	ret = iwl_alive_notify(priv);
	if (ret) {
		IWL_WARN(priv,
			"Could not complete ALIVE transition: %d\n", ret);
		priv->cur_ucode = old_type;
		return ret;
	}

	return 0;
}