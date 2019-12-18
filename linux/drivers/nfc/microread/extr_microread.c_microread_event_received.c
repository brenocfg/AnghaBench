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
typedef  size_t u8 ;
struct sk_buff {int len; int /*<<< orphan*/ * data; } ;
struct nfc_hci_dev {int /*<<< orphan*/  ndev; TYPE_1__* pipes; } ;
struct TYPE_2__ {size_t gate; } ;

/* Variables and functions */
 int EIO ; 
 int EPROTO ; 
#define  MICROREAD_EVT_MCARD_EXCHANGE 134 
#define  MICROREAD_EVT_MCARD_FIELD_OFF 133 
#define  MICROREAD_EVT_MCARD_FIELD_ON 132 
#define  MICROREAD_EVT_MREAD_CARD_FOUND 131 
 int /*<<< orphan*/  MICROREAD_EVT_MREAD_DISCOVERY_STOP ; 
#define  MICROREAD_EVT_P2P_INITIATOR_EXCHANGE_FROM_RF 130 
#define  MICROREAD_EVT_P2P_TARGET_ACTIVATED 129 
#define  MICROREAD_EVT_P2P_TARGET_DEACTIVATED 128 
 int /*<<< orphan*/  MICROREAD_GATE_ID_P2P_TARGET ; 
 int /*<<< orphan*/  MICROREAD_PAR_P2P_TARGET_MODE ; 
 int /*<<< orphan*/  NFC_COMM_PASSIVE ; 
 int /*<<< orphan*/  NFC_PROTO_NFC_DEP_MASK ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  microread_target_discovered (struct nfc_hci_dev*,size_t,struct sk_buff*) ; 
 int nfc_hci_send_event (struct nfc_hci_dev*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nfc_hci_set_param (struct nfc_hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*,int) ; 
 int nfc_tm_activated (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int nfc_tm_data_received (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  pr_info (char*,size_t,size_t) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int microread_event_received(struct nfc_hci_dev *hdev, u8 pipe,
				     u8 event, struct sk_buff *skb)
{
	int r;
	u8 gate = hdev->pipes[pipe].gate;
	u8 mode;

	pr_info("Microread received event 0x%x to gate 0x%x\n", event, gate);

	switch (event) {
	case MICROREAD_EVT_MREAD_CARD_FOUND:
		microread_target_discovered(hdev, gate, skb);
		return 0;

	case MICROREAD_EVT_P2P_INITIATOR_EXCHANGE_FROM_RF:
		if (skb->len < 1) {
			kfree_skb(skb);
			return -EPROTO;
		}

		if (skb->data[skb->len - 1]) {
			kfree_skb(skb);
			return -EIO;
		}

		skb_trim(skb, skb->len - 1);

		r = nfc_tm_data_received(hdev->ndev, skb);
		break;

	case MICROREAD_EVT_MCARD_FIELD_ON:
	case MICROREAD_EVT_MCARD_FIELD_OFF:
		kfree_skb(skb);
		return 0;

	case MICROREAD_EVT_P2P_TARGET_ACTIVATED:
		r = nfc_tm_activated(hdev->ndev, NFC_PROTO_NFC_DEP_MASK,
				     NFC_COMM_PASSIVE, skb->data,
				     skb->len);

		kfree_skb(skb);
		break;

	case MICROREAD_EVT_MCARD_EXCHANGE:
		if (skb->len < 1) {
			kfree_skb(skb);
			return -EPROTO;
		}

		if (skb->data[skb->len-1]) {
			kfree_skb(skb);
			return -EIO;
		}

		skb_trim(skb, skb->len - 1);

		r = nfc_tm_data_received(hdev->ndev, skb);
		break;

	case MICROREAD_EVT_P2P_TARGET_DEACTIVATED:
		kfree_skb(skb);

		mode = 0xff;
		r = nfc_hci_set_param(hdev, MICROREAD_GATE_ID_P2P_TARGET,
				      MICROREAD_PAR_P2P_TARGET_MODE, &mode, 1);
		if (r)
			break;

		r = nfc_hci_send_event(hdev, gate,
				       MICROREAD_EVT_MREAD_DISCOVERY_STOP, NULL,
				       0);
		break;

	default:
		return 1;
	}

	return r;
}