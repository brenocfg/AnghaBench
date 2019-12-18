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
typedef  int u16 ;
struct TYPE_3__ {scalar_t__ iftype; } ;
struct qtnf_vif {int /*<<< orphan*/  netdev; int /*<<< orphan*/  vifid; TYPE_2__* mac; TYPE_1__ wdev; } ;
struct qlink_event_bss_leave {int /*<<< orphan*/  reason; } ;
struct TYPE_4__ {int /*<<< orphan*/  macid; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPROTO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  cfg80211_disconnected (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
qtnf_event_handle_bss_leave(struct qtnf_vif *vif,
			    const struct qlink_event_bss_leave *leave_info,
			    u16 len)
{
	if (unlikely(len < sizeof(*leave_info))) {
		pr_err("VIF%u.%u: payload is too short (%u < %zu)\n",
		       vif->mac->macid, vif->vifid, len,
		       sizeof(struct qlink_event_bss_leave));
		return -EINVAL;
	}

	if (vif->wdev.iftype != NL80211_IFTYPE_STATION) {
		pr_err("VIF%u.%u: BSS_LEAVE event when not in STA mode\n",
		       vif->mac->macid, vif->vifid);
		return -EPROTO;
	}

	pr_debug("VIF%u.%u: disconnected\n", vif->mac->macid, vif->vifid);

	cfg80211_disconnected(vif->netdev, le16_to_cpu(leave_info->reason),
			      NULL, 0, 0, GFP_KERNEL);
	netif_carrier_off(vif->netdev);

	return 0;
}