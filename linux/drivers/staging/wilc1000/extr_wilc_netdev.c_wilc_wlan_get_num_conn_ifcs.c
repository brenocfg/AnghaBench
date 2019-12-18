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
typedef  size_t u8 ;
struct wilc {size_t vif_num; TYPE_1__** vif; } ;
struct TYPE_2__ {int /*<<< orphan*/  bssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  is_zero_ether_addr (int /*<<< orphan*/ ) ; 

int wilc_wlan_get_num_conn_ifcs(struct wilc *wilc)
{
	u8 i = 0;
	u8 ret_val = 0;

	for (i = 0; i < wilc->vif_num; i++)
		if (!is_zero_ether_addr(wilc->vif[i]->bssid))
			ret_val++;

	return ret_val;
}