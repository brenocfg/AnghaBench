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
struct wilc {void* mac_status; int /*<<< orphan*/  sync_event; } ;
typedef  void* s8 ;

/* Variables and functions */
 int /*<<< orphan*/  WID_STATUS ; 
 void* WILC_MAC_STATUS_INIT ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wilc_wlan_cfg_get_val (struct wilc*,int /*<<< orphan*/ ,void**,int) ; 

void wilc_mac_indicate(struct wilc *wilc)
{
	s8 status;

	wilc_wlan_cfg_get_val(wilc, WID_STATUS, &status, 1);
	if (wilc->mac_status == WILC_MAC_STATUS_INIT) {
		wilc->mac_status = status;
		complete(&wilc->sync_event);
	} else {
		wilc->mac_status = status;
	}
}