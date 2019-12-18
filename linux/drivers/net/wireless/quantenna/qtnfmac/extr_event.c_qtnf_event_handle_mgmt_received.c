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
struct qtnf_vif {int /*<<< orphan*/  wdev; TYPE_2__* netdev; int /*<<< orphan*/  vifid; TYPE_1__* mac; } ;
struct qlink_event_rxmgmt {scalar_t__ frame_data; int /*<<< orphan*/  sig_dbm; int /*<<< orphan*/  freq; int /*<<< orphan*/  flags; } ;
struct ieee80211_hdr_3addr {int /*<<< orphan*/  addr2; int /*<<< orphan*/  frame_control; } ;
typedef  enum nl80211_rxmgmt_flags { ____Placeholder_nl80211_rxmgmt_flags } nl80211_rxmgmt_flags ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  macid; } ;

/* Variables and functions */
 int EINVAL ; 
 int NL80211_RXMGMT_FLAG_ANSWERED ; 
 int QLINK_RXMGMT_FLAG_ANSWERED ; 
 int /*<<< orphan*/  cfg80211_rx_mgmt (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,scalar_t__,int const,int) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,size_t const) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
qtnf_event_handle_mgmt_received(struct qtnf_vif *vif,
				const struct qlink_event_rxmgmt *rxmgmt,
				u16 len)
{
	const size_t min_len = sizeof(*rxmgmt) +
			       sizeof(struct ieee80211_hdr_3addr);
	const struct ieee80211_hdr_3addr *frame = (void *)rxmgmt->frame_data;
	const u16 frame_len = len - sizeof(*rxmgmt);
	enum nl80211_rxmgmt_flags flags = 0;

	if (unlikely(len < min_len)) {
		pr_err("VIF%u.%u: payload is too short (%u < %zu)\n",
		       vif->mac->macid, vif->vifid, len, min_len);
		return -EINVAL;
	}

	if (le32_to_cpu(rxmgmt->flags) & QLINK_RXMGMT_FLAG_ANSWERED)
		flags |= NL80211_RXMGMT_FLAG_ANSWERED;

	pr_debug("%s LEN:%u FC:%.4X SA:%pM\n", vif->netdev->name, frame_len,
		 le16_to_cpu(frame->frame_control), frame->addr2);

	cfg80211_rx_mgmt(&vif->wdev, le32_to_cpu(rxmgmt->freq), rxmgmt->sig_dbm,
			 rxmgmt->frame_data, frame_len, flags);

	return 0;
}