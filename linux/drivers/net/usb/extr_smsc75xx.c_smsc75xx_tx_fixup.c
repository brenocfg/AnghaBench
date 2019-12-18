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
typedef  int u32 ;
typedef  int u16 ;
struct usbnet {int dummy; } ;
struct sk_buff {int len; scalar_t__ ip_summed; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {int /*<<< orphan*/  gso_size; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_PARTIAL ; 
 int /*<<< orphan*/  SMSC75XX_TX_OVERHEAD ; 
 int TX_CMD_A_FCS ; 
 int TX_CMD_A_IPE ; 
 int TX_CMD_A_LEN ; 
 int TX_CMD_A_LSO ; 
 int TX_CMD_A_TPE ; 
 int TX_CMD_B_MSS ; 
 int TX_CMD_B_MSS_SHIFT ; 
 int /*<<< orphan*/  TX_MSS_MIN ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_unaligned_le32 (int,void*) ; 
 scalar_t__ skb_cow_head (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_is_gso (struct sk_buff*) ; 
 void* skb_push (struct sk_buff*,int) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static struct sk_buff *smsc75xx_tx_fixup(struct usbnet *dev,
					 struct sk_buff *skb, gfp_t flags)
{
	u32 tx_cmd_a, tx_cmd_b;
	void *ptr;

	if (skb_cow_head(skb, SMSC75XX_TX_OVERHEAD)) {
		dev_kfree_skb_any(skb);
		return NULL;
	}

	tx_cmd_a = (u32)(skb->len & TX_CMD_A_LEN) | TX_CMD_A_FCS;

	if (skb->ip_summed == CHECKSUM_PARTIAL)
		tx_cmd_a |= TX_CMD_A_IPE | TX_CMD_A_TPE;

	if (skb_is_gso(skb)) {
		u16 mss = max(skb_shinfo(skb)->gso_size, TX_MSS_MIN);
		tx_cmd_b = (mss << TX_CMD_B_MSS_SHIFT) & TX_CMD_B_MSS;

		tx_cmd_a |= TX_CMD_A_LSO;
	} else {
		tx_cmd_b = 0;
	}

	ptr = skb_push(skb, 8);
	put_unaligned_le32(tx_cmd_a, ptr);
	put_unaligned_le32(tx_cmd_b, ptr + 4);

	return skb;
}