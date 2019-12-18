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
typedef  int /*<<< orphan*/  u8 ;
struct wilc_vif {int dummy; } ;
struct wid {int size; int /*<<< orphan*/ * val; int /*<<< orphan*/  type; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  WID_CHAR ; 
 int /*<<< orphan*/  WID_TX_POWER ; 
 int /*<<< orphan*/  WILC_SET_CFG ; 
 int wilc_send_config_pkt (struct wilc_vif*,int /*<<< orphan*/ ,struct wid*,int) ; 

int wilc_set_tx_power(struct wilc_vif *vif, u8 tx_power)
{
	struct wid wid;

	wid.id = WID_TX_POWER;
	wid.type = WID_CHAR;
	wid.val = &tx_power;
	wid.size = sizeof(char);

	return wilc_send_config_pkt(vif, WILC_SET_CFG, &wid, 1);
}