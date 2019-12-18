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
struct TYPE_2__ {int /*<<< orphan*/  wt_timeout; int /*<<< orphan*/  atr; } ;
struct st21nfca_hci_info {TYPE_1__ se_info; } ;
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct nfc_hci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ST21NFCA_APDU_READER_GATE ; 
 int /*<<< orphan*/  ST21NFCA_BWI_TO_TIMEOUT (int /*<<< orphan*/ ) ; 
 scalar_t__ ST21NFCA_ESE_MAX_LENGTH ; 
 int /*<<< orphan*/  ST21NFCA_PARAM_ATR ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 struct st21nfca_hci_info* nfc_hci_get_clientdata (struct nfc_hci_dev*) ; 
 int nfc_hci_get_param (struct nfc_hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff**) ; 
 int /*<<< orphan*/  st21nfca_se_get_bwi (struct nfc_hci_dev*) ; 

__attribute__((used)) static void st21nfca_se_get_atr(struct nfc_hci_dev *hdev)
{
	int r;
	struct sk_buff *skb;
	struct st21nfca_hci_info *info = nfc_hci_get_clientdata(hdev);

	r = nfc_hci_get_param(hdev, ST21NFCA_APDU_READER_GATE,
			ST21NFCA_PARAM_ATR, &skb);
	if (r < 0)
		return;

	if (skb->len <= ST21NFCA_ESE_MAX_LENGTH) {
		memcpy(info->se_info.atr, skb->data, skb->len);
		info->se_info.wt_timeout =
			ST21NFCA_BWI_TO_TIMEOUT(st21nfca_se_get_bwi(hdev));
	}
	kfree_skb(skb);
}