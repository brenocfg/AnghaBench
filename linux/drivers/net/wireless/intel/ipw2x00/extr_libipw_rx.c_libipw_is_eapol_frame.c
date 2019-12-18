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
typedef  int u16 ;
struct sk_buff {int len; int* data; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct libipw_hdr_3addr {int /*<<< orphan*/  addr1; int /*<<< orphan*/  addr3; int /*<<< orphan*/  frame_ctl; } ;
struct libipw_device {struct net_device* dev; } ;

/* Variables and functions */
 int ETH_P_PAE ; 
 int IEEE80211_FCTL_FROMDS ; 
 int IEEE80211_FCTL_TODS ; 
 scalar_t__ ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int libipw_is_eapol_frame(struct libipw_device *ieee,
				    struct sk_buff *skb)
{
	struct net_device *dev = ieee->dev;
	u16 fc, ethertype;
	struct libipw_hdr_3addr *hdr;
	u8 *pos;

	if (skb->len < 24)
		return 0;

	hdr = (struct libipw_hdr_3addr *)skb->data;
	fc = le16_to_cpu(hdr->frame_ctl);

	/* check that the frame is unicast frame to us */
	if ((fc & (IEEE80211_FCTL_TODS | IEEE80211_FCTL_FROMDS)) ==
	    IEEE80211_FCTL_TODS &&
	    ether_addr_equal(hdr->addr1, dev->dev_addr) &&
	    ether_addr_equal(hdr->addr3, dev->dev_addr)) {
		/* ToDS frame with own addr BSSID and DA */
	} else if ((fc & (IEEE80211_FCTL_TODS | IEEE80211_FCTL_FROMDS)) ==
		   IEEE80211_FCTL_FROMDS &&
		   ether_addr_equal(hdr->addr1, dev->dev_addr)) {
		/* FromDS frame with own addr as DA */
	} else
		return 0;

	if (skb->len < 24 + 8)
		return 0;

	/* check for port access entity Ethernet type */
	pos = skb->data + 24;
	ethertype = (pos[6] << 8) | pos[7];
	if (ethertype == ETH_P_PAE)
		return 1;

	return 0;
}