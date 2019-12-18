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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct wilc_vif {scalar_t__ monitor_flag; TYPE_2__* frame_reg; } ;
struct wilc {int vif_num; int /*<<< orphan*/  vif_mutex; int /*<<< orphan*/  monitor_dev; TYPE_1__** vif; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_4__ {scalar_t__ type; scalar_t__ reg; } ;
struct TYPE_3__ {int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 scalar_t__ le16_to_cpup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct wilc_vif* netdev_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wilc_wfi_monitor_rx (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wilc_wfi_p2p_rx (struct wilc_vif*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void wilc_wfi_mgmt_rx(struct wilc *wilc, u8 *buff, u32 size)
{
	int i = 0;
	struct wilc_vif *vif;

	mutex_lock(&wilc->vif_mutex);
	for (i = 0; i < wilc->vif_num; i++) {
		u16 type = le16_to_cpup((__le16 *)buff);

		vif = netdev_priv(wilc->vif[i]->ndev);
		if ((type == vif->frame_reg[0].type && vif->frame_reg[0].reg) ||
		    (type == vif->frame_reg[1].type && vif->frame_reg[1].reg)) {
			wilc_wfi_p2p_rx(vif, buff, size);
			break;
		}

		if (vif->monitor_flag) {
			wilc_wfi_monitor_rx(wilc->monitor_dev, buff, size);
			break;
		}
	}
	mutex_unlock(&wilc->vif_mutex);
}