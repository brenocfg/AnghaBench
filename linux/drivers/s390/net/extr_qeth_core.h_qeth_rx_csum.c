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
typedef  int u8 ;
struct sk_buff {int /*<<< orphan*/  ip_summed; } ;
struct qeth_card {TYPE_1__* dev; } ;
struct TYPE_2__ {int features; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int NETIF_F_RXCSUM ; 
 int /*<<< orphan*/  QETH_CARD_STAT_INC (struct qeth_card*,int /*<<< orphan*/ ) ; 
 int QETH_HDR_EXT_CSUM_TRANSP_REQ ; 
 int /*<<< orphan*/  rx_skb_csum ; 

__attribute__((used)) static inline void qeth_rx_csum(struct qeth_card *card, struct sk_buff *skb,
				u8 flags)
{
	if ((card->dev->features & NETIF_F_RXCSUM) &&
	    (flags & QETH_HDR_EXT_CSUM_TRANSP_REQ)) {
		skb->ip_summed = CHECKSUM_UNNECESSARY;
		QETH_CARD_STAT_INC(card, rx_skb_csum);
	} else {
		skb->ip_summed = CHECKSUM_NONE;
	}
}