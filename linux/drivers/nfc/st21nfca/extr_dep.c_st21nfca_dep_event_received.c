#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_3__ {int /*<<< orphan*/  curr_nfc_dep_pni; } ;
struct st21nfca_hci_info {TYPE_1__ dep_info; } ;
struct sk_buff {int dummy; } ;
struct nfc_hci_dev {TYPE_2__* ndev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  ST21NFCA_EVT_CARD_ACTIVATED 132 
#define  ST21NFCA_EVT_CARD_DEACTIVATED 131 
#define  ST21NFCA_EVT_FIELD_OFF 130 
#define  ST21NFCA_EVT_FIELD_ON 129 
#define  ST21NFCA_EVT_SEND_DATA 128 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  nfc_err (int /*<<< orphan*/ *,char*) ; 
 struct st21nfca_hci_info* nfc_hci_get_clientdata (struct nfc_hci_dev*) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int st21nfca_tm_event_send_data (struct nfc_hci_dev*,struct sk_buff*) ; 

int st21nfca_dep_event_received(struct nfc_hci_dev *hdev,
				u8 event, struct sk_buff *skb)
{
	int r = 0;
	struct st21nfca_hci_info *info = nfc_hci_get_clientdata(hdev);

	pr_debug("dep event: %d\n", event);

	switch (event) {
	case ST21NFCA_EVT_CARD_ACTIVATED:
		info->dep_info.curr_nfc_dep_pni = 0;
		break;
	case ST21NFCA_EVT_CARD_DEACTIVATED:
		break;
	case ST21NFCA_EVT_FIELD_ON:
		break;
	case ST21NFCA_EVT_FIELD_OFF:
		break;
	case ST21NFCA_EVT_SEND_DATA:
		r = st21nfca_tm_event_send_data(hdev, skb);
		if (r < 0)
			return r;
		return 0;
	default:
		nfc_err(&hdev->ndev->dev, "Unexpected event on card f gate\n");
		return 1;
	}
	kfree_skb(skb);
	return r;
}