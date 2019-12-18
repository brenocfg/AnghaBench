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
typedef  int u8 ;
struct ath_common {int dummy; } ;
struct ath9k_htc_priv {int* vif_sta_pos; size_t mon_vif_idx; int sta_slot; TYPE_1__* ah; int /*<<< orphan*/  nstations; } ;
struct TYPE_2__ {int is_monitoring; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG ; 
 int /*<<< orphan*/  WMI_CMD_BUF (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  WMI_NODE_REMOVE_CMDID ; 
 int /*<<< orphan*/  __ath9k_htc_remove_monitor_interface (struct ath9k_htc_priv*) ; 
 struct ath_common* ath9k_hw_common (TYPE_1__*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,size_t,int) ; 
 int /*<<< orphan*/  ath_err (struct ath_common*,char*) ; 

__attribute__((used)) static int ath9k_htc_remove_monitor_interface(struct ath9k_htc_priv *priv)
{
	struct ath_common *common = ath9k_hw_common(priv->ah);
	int ret = 0;
	u8 cmd_rsp, sta_idx;

	__ath9k_htc_remove_monitor_interface(priv);

	sta_idx = priv->vif_sta_pos[priv->mon_vif_idx];

	WMI_CMD_BUF(WMI_NODE_REMOVE_CMDID, &sta_idx);
	if (ret) {
		ath_err(common, "Unable to remove station entry for monitor mode\n");
		return ret;
	}

	priv->sta_slot &= ~(1 << sta_idx);
	priv->nstations--;
	priv->ah->is_monitoring = false;

	ath_dbg(common, CONFIG,
		"Removed a monitor interface at idx: %d, sta idx: %d\n",
		priv->mon_vif_idx, sta_idx);

	return 0;
}