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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct wol_config {int dummy; } ;
struct lbs_private {int /*<<< orphan*/  dev; int /*<<< orphan*/  wol_gap; int /*<<< orphan*/  wol_gpio; int /*<<< orphan*/  ehs_remove_supported; } ;
struct TYPE_3__ {int /*<<< orphan*/  action; } ;
struct TYPE_4__ {int /*<<< orphan*/  size; } ;
struct cmd_ds_host_sleep {TYPE_1__ wol_conf; TYPE_2__ hdr; int /*<<< orphan*/  gap; int /*<<< orphan*/  gpio; int /*<<< orphan*/  criteria; } ;
typedef  int /*<<< orphan*/  cmd_config ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_802_11_HOST_SLEEP_CFG ; 
 int /*<<< orphan*/  CMD_ACT_ACTION_NONE ; 
 scalar_t__ EHS_REMOVE_WAKEUP ; 
 int __lbs_cmd (struct lbs_private*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__) ; 
 int /*<<< orphan*/  lbs_ret_host_sleep_cfg ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,int) ; 

int lbs_host_sleep_cfg(struct lbs_private *priv, uint32_t criteria,
		struct wol_config *p_wol_config)
{
	struct cmd_ds_host_sleep cmd_config;
	int ret;

	/*
	 * Certain firmware versions do not support EHS_REMOVE_WAKEUP command
	 * and the card will return a failure.  Since we need to be
	 * able to reset the mask, in those cases we set a 0 mask instead.
	 */
	if (criteria == EHS_REMOVE_WAKEUP && !priv->ehs_remove_supported)
		criteria = 0;

	cmd_config.hdr.size = cpu_to_le16(sizeof(cmd_config));
	cmd_config.criteria = cpu_to_le32(criteria);
	cmd_config.gpio = priv->wol_gpio;
	cmd_config.gap = priv->wol_gap;

	if (p_wol_config != NULL)
		memcpy((uint8_t *)&cmd_config.wol_conf, (uint8_t *)p_wol_config,
				sizeof(struct wol_config));
	else
		cmd_config.wol_conf.action = CMD_ACT_ACTION_NONE;

	ret = __lbs_cmd(priv, CMD_802_11_HOST_SLEEP_CFG, &cmd_config.hdr,
			le16_to_cpu(cmd_config.hdr.size),
			lbs_ret_host_sleep_cfg, 0);
	if (!ret) {
		if (p_wol_config)
			memcpy((uint8_t *) p_wol_config,
					(uint8_t *)&cmd_config.wol_conf,
					sizeof(struct wol_config));
	} else {
		netdev_info(priv->dev, "HOST_SLEEP_CFG failed %d\n", ret);
	}

	return ret;
}