#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mwifiex_private {int sched_scanning; TYPE_1__* adapter; } ;
struct mwifiex_bg_scan_cfg {int enable; int /*<<< orphan*/  action; int /*<<< orphan*/  bss_type; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HostCmd_ACT_GEN_SET ; 
 int /*<<< orphan*/  HostCmd_CMD_802_11_BG_SCAN_CONFIG ; 
 int /*<<< orphan*/  MWIFIEX_BGSCAN_ACT_SET ; 
 int /*<<< orphan*/  MWIFIEX_BSS_MODE_INFRA ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kfree (struct mwifiex_bg_scan_cfg*) ; 
 struct mwifiex_bg_scan_cfg* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ mwifiex_send_cmd (struct mwifiex_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mwifiex_bg_scan_cfg*,int) ; 

int mwifiex_stop_bg_scan(struct mwifiex_private *priv)
{
	struct mwifiex_bg_scan_cfg *bgscan_cfg;

	if (!priv->sched_scanning) {
		dev_dbg(priv->adapter->dev, "bgscan already stopped!\n");
		return 0;
	}

	bgscan_cfg = kzalloc(sizeof(*bgscan_cfg), GFP_KERNEL);
	if (!bgscan_cfg)
		return -ENOMEM;

	bgscan_cfg->bss_type = MWIFIEX_BSS_MODE_INFRA;
	bgscan_cfg->action = MWIFIEX_BGSCAN_ACT_SET;
	bgscan_cfg->enable = false;

	if (mwifiex_send_cmd(priv, HostCmd_CMD_802_11_BG_SCAN_CONFIG,
			     HostCmd_ACT_GEN_SET, 0, bgscan_cfg, true)) {
		kfree(bgscan_cfg);
		return -EFAULT;
	}

	kfree(bgscan_cfg);
	priv->sched_scanning = false;

	return 0;
}