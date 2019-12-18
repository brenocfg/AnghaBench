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
struct sk_buff {int dummy; } ;
struct nfc_hci_dev {TYPE_1__* pipes; } ;
struct TYPE_2__ {size_t gate; size_t dest_host; } ;

/* Variables and functions */
#define  NFC_HCI_ADMIN_GATE 132 
#define  NFC_HCI_LOOPBACK_GATE 131 
#define  ST21NFCA_APDU_READER_GATE 130 
#define  ST21NFCA_CONNECTIVITY_GATE 129 
#define  ST21NFCA_RF_CARD_F_GATE 128 
 int /*<<< orphan*/  pr_debug (char*,size_t,size_t) ; 
 int st21nfca_admin_event_received (struct nfc_hci_dev*,size_t,struct sk_buff*) ; 
 int st21nfca_apdu_reader_event_received (struct nfc_hci_dev*,size_t,struct sk_buff*) ; 
 int st21nfca_connectivity_event_received (struct nfc_hci_dev*,size_t,size_t,struct sk_buff*) ; 
 int st21nfca_dep_event_received (struct nfc_hci_dev*,size_t,struct sk_buff*) ; 
 int st21nfca_hci_loopback_event_received (struct nfc_hci_dev*,size_t,struct sk_buff*) ; 

__attribute__((used)) static int st21nfca_hci_event_received(struct nfc_hci_dev *hdev, u8 pipe,
				       u8 event, struct sk_buff *skb)
{
	u8 gate = hdev->pipes[pipe].gate;
	u8 host = hdev->pipes[pipe].dest_host;

	pr_debug("hci event: %d gate: %x\n", event, gate);

	switch (gate) {
	case NFC_HCI_ADMIN_GATE:
		return st21nfca_admin_event_received(hdev, event, skb);
	case ST21NFCA_RF_CARD_F_GATE:
		return st21nfca_dep_event_received(hdev, event, skb);
	case ST21NFCA_CONNECTIVITY_GATE:
		return st21nfca_connectivity_event_received(hdev, host,
							event, skb);
	case ST21NFCA_APDU_READER_GATE:
		return st21nfca_apdu_reader_event_received(hdev, event, skb);
	case NFC_HCI_LOOPBACK_GATE:
		return st21nfca_hci_loopback_event_received(hdev, event, skb);
	default:
		return 1;
	}
}