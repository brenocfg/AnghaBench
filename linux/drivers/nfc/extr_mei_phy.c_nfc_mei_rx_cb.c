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
struct sk_buff {int /*<<< orphan*/  data; } ;
struct nfc_mei_phy {scalar_t__ hard_fault; int /*<<< orphan*/  hdev; } ;
struct mei_cl_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MEI_DUMP_SKB_IN (char*,struct sk_buff*) ; 
 int MEI_NFC_HEADER_SIZE ; 
 int /*<<< orphan*/  MEI_NFC_MAX_READ ; 
 struct sk_buff* alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct nfc_mei_phy* mei_cldev_get_drvdata (struct mei_cl_device*) ; 
 int mei_nfc_recv (struct nfc_mei_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfc_hci_recv_frame (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 

__attribute__((used)) static void nfc_mei_rx_cb(struct mei_cl_device *cldev)
{
	struct nfc_mei_phy *phy = mei_cldev_get_drvdata(cldev);
	struct sk_buff *skb;
	int reply_size;

	if (!phy)
		return;

	if (phy->hard_fault != 0)
		return;

	skb = alloc_skb(MEI_NFC_MAX_READ, GFP_KERNEL);
	if (!skb)
		return;

	reply_size = mei_nfc_recv(phy, skb->data, MEI_NFC_MAX_READ);
	if (reply_size < MEI_NFC_HEADER_SIZE) {
		kfree_skb(skb);
		return;
	}

	skb_put(skb, reply_size);
	skb_pull(skb, MEI_NFC_HEADER_SIZE);

	MEI_DUMP_SKB_IN("mei frame read", skb);

	nfc_hci_recv_frame(phy->hdev, skb);
}