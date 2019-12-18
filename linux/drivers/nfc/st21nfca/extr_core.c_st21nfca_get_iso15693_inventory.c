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
struct sk_buff {scalar_t__ len; int /*<<< orphan*/ * data; } ;
struct nfc_target {int is_iso15693; int /*<<< orphan*/  iso15693_dsfid; int /*<<< orphan*/  iso15693_uid; } ;
struct nfc_hci_dev {int dummy; } ;

/* Variables and functions */
 int EPROTO ; 
 scalar_t__ NFC_ISO15693_UID_MAXSIZE ; 
 int /*<<< orphan*/  ST21NFCA_RF_READER_ISO15693_GATE ; 
 int /*<<< orphan*/  ST21NFCA_RF_READER_ISO15693_INVENTORY ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int nfc_hci_get_param (struct nfc_hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff**) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 

__attribute__((used)) static int st21nfca_get_iso15693_inventory(struct nfc_hci_dev *hdev,
					   struct nfc_target *target)
{
	int r;
	struct sk_buff *inventory_skb = NULL;

	r = nfc_hci_get_param(hdev, ST21NFCA_RF_READER_ISO15693_GATE,
			      ST21NFCA_RF_READER_ISO15693_INVENTORY,
			      &inventory_skb);
	if (r < 0)
		goto exit;

	skb_pull(inventory_skb, 2);

	if (inventory_skb->len == 0 ||
	    inventory_skb->len > NFC_ISO15693_UID_MAXSIZE) {
		r = -EPROTO;
		goto exit;
	}

	memcpy(target->iso15693_uid, inventory_skb->data, inventory_skb->len);
	target->iso15693_dsfid	= inventory_skb->data[1];
	target->is_iso15693 = 1;
exit:
	kfree_skb(inventory_skb);
	return r;
}