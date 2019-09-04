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
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {int /*<<< orphan*/  byte_tx; int /*<<< orphan*/  cmd_tx; int /*<<< orphan*/  err_tx; int /*<<< orphan*/  acl_tx; } ;
struct hci_dev {TYPE_1__ stat; } ;
struct btqcomsmd {int /*<<< orphan*/  cmd_channel; int /*<<< orphan*/  acl_channel; } ;

/* Variables and functions */
 int EILSEQ ; 
#define  HCI_ACLDATA_PKT 129 
#define  HCI_COMMAND_PKT 128 
 struct btqcomsmd* hci_get_drvdata (struct hci_dev*) ; 
 int hci_skb_pkt_type (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int rpmsg_send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int btqcomsmd_send(struct hci_dev *hdev, struct sk_buff *skb)
{
	struct btqcomsmd *btq = hci_get_drvdata(hdev);
	int ret;

	switch (hci_skb_pkt_type(skb)) {
	case HCI_ACLDATA_PKT:
		ret = rpmsg_send(btq->acl_channel, skb->data, skb->len);
		if (ret) {
			hdev->stat.err_tx++;
			break;
		}
		hdev->stat.acl_tx++;
		hdev->stat.byte_tx += skb->len;
		break;
	case HCI_COMMAND_PKT:
		ret = rpmsg_send(btq->cmd_channel, skb->data, skb->len);
		if (ret) {
			hdev->stat.err_tx++;
			break;
		}
		hdev->stat.cmd_tx++;
		hdev->stat.byte_tx += skb->len;
		break;
	default:
		ret = -EILSEQ;
		break;
	}

	if (!ret)
		kfree_skb(skb);

	return ret;
}