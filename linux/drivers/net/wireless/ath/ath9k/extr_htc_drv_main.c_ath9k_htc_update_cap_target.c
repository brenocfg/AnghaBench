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
typedef  int /*<<< orphan*/  u8 ;
struct ath9k_htc_priv {TYPE_2__* ah; } ;
struct ath9k_htc_cap_target {int ampdu_subframes; int /*<<< orphan*/  tx_chainmask; int /*<<< orphan*/  enable_coex; int /*<<< orphan*/  ampdu_limit; } ;
struct TYPE_3__ {int /*<<< orphan*/  tx_chainmask; } ;
struct TYPE_4__ {TYPE_1__ caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  WMI_CMD_BUF (int /*<<< orphan*/ ,struct ath9k_htc_cap_target*) ; 
 int /*<<< orphan*/  WMI_TARGET_IC_UPDATE_CMDID ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memset (struct ath9k_htc_cap_target*,int /*<<< orphan*/ ,int) ; 

int ath9k_htc_update_cap_target(struct ath9k_htc_priv *priv,
				u8 enable_coex)
{
	struct ath9k_htc_cap_target tcap;
	int ret;
	u8 cmd_rsp;

	memset(&tcap, 0, sizeof(struct ath9k_htc_cap_target));

	tcap.ampdu_limit = cpu_to_be32(0xffff);
	tcap.ampdu_subframes = 0xff;
	tcap.enable_coex = enable_coex;
	tcap.tx_chainmask = priv->ah->caps.tx_chainmask;

	WMI_CMD_BUF(WMI_TARGET_IC_UPDATE_CMDID, &tcap);

	return ret;
}