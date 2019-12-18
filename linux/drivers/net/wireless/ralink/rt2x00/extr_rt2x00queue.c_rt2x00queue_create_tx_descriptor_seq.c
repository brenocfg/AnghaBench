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
typedef  int /*<<< orphan*/  u16 ;
struct txentry_desc {int /*<<< orphan*/  flags; } ;
struct sk_buff {scalar_t__ data; } ;
struct rt2x00_intf {int /*<<< orphan*/  seqno; } ;
struct rt2x00_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  vif; } ;
struct ieee80211_tx_info {int flags; TYPE_1__ control; } ;
struct ieee80211_hdr {int /*<<< orphan*/  seq_ctrl; int /*<<< orphan*/  frame_control; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTRY_TXD_FIRST_FRAGMENT ; 
 int /*<<< orphan*/  ENTRY_TXD_GENERATE_SEQ ; 
 int /*<<< orphan*/  IEEE80211_SCTL_FRAG ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_TX_CTL_ASSIGN_SEQ ; 
 int /*<<< orphan*/  REQUIRE_SW_SEQNO ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_add_return (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_beacon (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_has_cap_flag (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct rt2x00_intf* vif_to_intf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rt2x00queue_create_tx_descriptor_seq(struct rt2x00_dev *rt2x00dev,
						 struct sk_buff *skb,
						 struct txentry_desc *txdesc)
{
	struct ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *)skb->data;
	struct rt2x00_intf *intf = vif_to_intf(tx_info->control.vif);
	u16 seqno;

	if (!(tx_info->flags & IEEE80211_TX_CTL_ASSIGN_SEQ))
		return;

	__set_bit(ENTRY_TXD_GENERATE_SEQ, &txdesc->flags);

	if (!rt2x00_has_cap_flag(rt2x00dev, REQUIRE_SW_SEQNO)) {
		/*
		 * rt2800 has a H/W (or F/W) bug, device incorrectly increase
		 * seqno on retransmitted data (non-QOS) and management frames.
		 * To workaround the problem let's generate seqno in software.
		 * Except for beacons which are transmitted periodically by H/W
		 * hence hardware has to assign seqno for them.
		 */
	    	if (ieee80211_is_beacon(hdr->frame_control)) {
			__set_bit(ENTRY_TXD_GENERATE_SEQ, &txdesc->flags);
			/* H/W will generate sequence number */
			return;
		}

		__clear_bit(ENTRY_TXD_GENERATE_SEQ, &txdesc->flags);
	}

	/*
	 * The hardware is not able to insert a sequence number. Assign a
	 * software generated one here.
	 *
	 * This is wrong because beacons are not getting sequence
	 * numbers assigned properly.
	 *
	 * A secondary problem exists for drivers that cannot toggle
	 * sequence counting per-frame, since those will override the
	 * sequence counter given by mac80211.
	 */
	if (test_bit(ENTRY_TXD_FIRST_FRAGMENT, &txdesc->flags))
		seqno = atomic_add_return(0x10, &intf->seqno);
	else
		seqno = atomic_read(&intf->seqno);

	hdr->seq_ctrl &= cpu_to_le16(IEEE80211_SCTL_FRAG);
	hdr->seq_ctrl |= cpu_to_le16(seqno);
}