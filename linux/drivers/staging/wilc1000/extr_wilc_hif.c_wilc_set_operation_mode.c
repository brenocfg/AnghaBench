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
typedef  int u8 ;
struct wilc_vif {int /*<<< orphan*/  ndev; } ;
struct wilc_drv_handler {int mode; int /*<<< orphan*/  handler; } ;
struct wid {int size; int* val; int /*<<< orphan*/  type; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  drv ;

/* Variables and functions */
 int /*<<< orphan*/  WID_SET_OPERATION_MODE ; 
 int /*<<< orphan*/  WID_STR ; 
 int /*<<< orphan*/  WILC_SET_CFG ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int wilc_send_config_pkt (struct wilc_vif*,int /*<<< orphan*/ ,struct wid*,int) ; 

int wilc_set_operation_mode(struct wilc_vif *vif, int index, u8 mode,
			    u8 ifc_id)
{
	struct wid wid;
	int result;
	struct wilc_drv_handler drv;

	wid.id = WID_SET_OPERATION_MODE;
	wid.type = WID_STR;
	wid.size = sizeof(drv);
	wid.val = (u8 *)&drv;

	drv.handler = cpu_to_le32(index);
	drv.mode = (ifc_id | (mode << 1));

	result = wilc_send_config_pkt(vif, WILC_SET_CFG, &wid, 1);
	if (result)
		netdev_err(vif->ndev, "Failed to set driver handler\n");

	return result;
}