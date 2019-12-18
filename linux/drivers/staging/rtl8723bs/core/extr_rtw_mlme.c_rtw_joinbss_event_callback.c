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
struct wlan_network {int /*<<< orphan*/  join_res; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlmeext_joinbss_event_callback (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_os_xmit_schedule (struct adapter*) ; 

void rtw_joinbss_event_callback(struct adapter *adapter, u8 *pbuf)
{
	struct wlan_network	*pnetwork	= (struct wlan_network *)pbuf;

	mlmeext_joinbss_event_callback(adapter, pnetwork->join_res);

	rtw_os_xmit_schedule(adapter);
}