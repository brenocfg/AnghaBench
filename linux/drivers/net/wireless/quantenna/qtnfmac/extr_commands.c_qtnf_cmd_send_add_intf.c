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
struct qtnf_vif {int dummy; } ;
typedef  enum nl80211_iftype { ____Placeholder_nl80211_iftype } nl80211_iftype ;

/* Variables and functions */
 int /*<<< orphan*/  QLINK_CMD_ADD_INTF ; 
 int qtnf_cmd_send_add_change_intf (struct qtnf_vif*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int qtnf_cmd_send_add_intf(struct qtnf_vif *vif, enum nl80211_iftype iftype,
			   int use4addr, u8 *mac_addr)
{
	return qtnf_cmd_send_add_change_intf(vif, iftype, use4addr, mac_addr,
			QLINK_CMD_ADD_INTF);
}