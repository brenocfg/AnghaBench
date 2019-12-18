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
struct sk_buff {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
struct nfc_hci_dev {int dummy; } ;
struct nfc_dev {int dummy; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HCI_DM_GET_DATA ; 
 int /*<<< orphan*/  NFC_ATTR_VENDOR_DATA ; 
 int /*<<< orphan*/  ST21NFCA_DEVICE_MGNT_GATE ; 
 int /*<<< orphan*/  ST21NFCA_HCI_DM_GETDATA ; 
 int /*<<< orphan*/  ST21NFCA_VENDOR_OUI ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct nfc_hci_dev* nfc_get_drvdata (struct nfc_dev*) ; 
 int nfc_hci_send_cmd (struct nfc_hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,size_t,struct sk_buff**) ; 
 struct sk_buff* nfc_vendor_cmd_alloc_reply_skb (struct nfc_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nfc_vendor_cmd_reply (struct sk_buff*) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int st21nfca_hci_dm_get_data(struct nfc_dev *dev, void *data,
				    size_t data_len)
{
	int r;
	struct sk_buff *msg, *skb;
	struct nfc_hci_dev *hdev = nfc_get_drvdata(dev);

	r = nfc_hci_send_cmd(hdev,
			     ST21NFCA_DEVICE_MGNT_GATE,
			     ST21NFCA_HCI_DM_GETDATA,
			     data, data_len, &skb);
	if (r)
		goto exit;

	msg = nfc_vendor_cmd_alloc_reply_skb(dev, ST21NFCA_VENDOR_OUI,
					     HCI_DM_GET_DATA, skb->len);
	if (!msg) {
		r = -ENOMEM;
		goto free_skb;
	}

	if (nla_put(msg, NFC_ATTR_VENDOR_DATA, skb->len, skb->data)) {
		kfree_skb(msg);
		r = -ENOBUFS;
		goto free_skb;
	}

	r = nfc_vendor_cmd_reply(msg);

free_skb:
	kfree_skb(skb);
exit:
	return r;
}