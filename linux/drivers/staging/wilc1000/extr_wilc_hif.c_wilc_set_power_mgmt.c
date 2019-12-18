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
typedef  int /*<<< orphan*/  u32 ;
struct wilc_vif {int /*<<< orphan*/  ndev; } ;
struct wid {int size; int /*<<< orphan*/ * val; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  s8 ;

/* Variables and functions */
 int /*<<< orphan*/  WID_POWER_MANAGEMENT ; 
 int /*<<< orphan*/  WILC_FW_MIN_FAST_PS ; 
 int /*<<< orphan*/  WILC_FW_NO_POWERSAVE ; 
 int /*<<< orphan*/  WILC_SET_CFG ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int wilc_send_config_pkt (struct wilc_vif*,int /*<<< orphan*/ ,struct wid*,int) ; 

int wilc_set_power_mgmt(struct wilc_vif *vif, bool enabled, u32 timeout)
{
	struct wid wid;
	int result;
	s8 power_mode;

	if (enabled)
		power_mode = WILC_FW_MIN_FAST_PS;
	else
		power_mode = WILC_FW_NO_POWERSAVE;

	wid.id = WID_POWER_MANAGEMENT;
	wid.val = &power_mode;
	wid.size = sizeof(char);
	result = wilc_send_config_pkt(vif, WILC_SET_CFG, &wid, 1);
	if (result)
		netdev_err(vif->ndev, "Failed to send power management\n");

	return result;
}