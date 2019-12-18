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
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct nfc_target {int /*<<< orphan*/  idx; int /*<<< orphan*/  hci_reader_gate; } ;
struct nfc_hci_dev {int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int EPROTO ; 
 int /*<<< orphan*/  MICROREAD_PAR_P2P_INITIATOR_GT ; 
 scalar_t__ NFC_GB_MAXSIZE ; 
 int /*<<< orphan*/  NFC_RF_INITIATOR ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int nfc_dep_link_is_up (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nfc_hci_get_param (struct nfc_hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff**) ; 
 int nfc_set_remote_general_bytes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int microread_dep_link_up(struct nfc_hci_dev *hdev,
				struct nfc_target *target, u8 comm_mode,
				u8 *gb, size_t gb_len)
{
	struct sk_buff *rgb_skb = NULL;
	int r;

	r = nfc_hci_get_param(hdev, target->hci_reader_gate,
			      MICROREAD_PAR_P2P_INITIATOR_GT, &rgb_skb);
	if (r < 0)
		return r;

	if (rgb_skb->len == 0 || rgb_skb->len > NFC_GB_MAXSIZE) {
		r = -EPROTO;
		goto exit;
	}

	r = nfc_set_remote_general_bytes(hdev->ndev, rgb_skb->data,
					 rgb_skb->len);
	if (r == 0)
		r = nfc_dep_link_is_up(hdev->ndev, target->idx, comm_mode,
				       NFC_RF_INITIATOR);
exit:
	kfree_skb(rgb_skb);

	return r;
}