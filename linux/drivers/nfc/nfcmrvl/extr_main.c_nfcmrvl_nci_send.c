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
struct sk_buff {unsigned char len; void* dev; } ;
struct TYPE_3__ {scalar_t__ hci_muxed; } ;
struct nfcmrvl_private {TYPE_2__* if_ops; TYPE_1__ config; int /*<<< orphan*/  dev; } ;
struct nci_dev {int dummy; } ;
struct TYPE_4__ {int (* nci_send ) (struct nfcmrvl_private*,struct sk_buff*) ;} ;

/* Variables and functions */
 unsigned char NFCMRVL_HCI_COMMAND_CODE ; 
 int /*<<< orphan*/  NFCMRVL_HCI_EVENT_HEADER_SIZE ; 
 unsigned char NFCMRVL_HCI_OCF ; 
 unsigned char NFCMRVL_HCI_OGF ; 
 struct nfcmrvl_private* nci_get_drvdata (struct nci_dev*) ; 
 int /*<<< orphan*/  nfc_info (int /*<<< orphan*/ ,char*,unsigned char) ; 
 unsigned char* skb_push (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int stub1 (struct nfcmrvl_private*,struct sk_buff*) ; 

__attribute__((used)) static int nfcmrvl_nci_send(struct nci_dev *ndev, struct sk_buff *skb)
{
	struct nfcmrvl_private *priv = nci_get_drvdata(ndev);

	nfc_info(priv->dev, "send entry, len %d\n", skb->len);

	skb->dev = (void *)ndev;

	if (priv->config.hci_muxed) {
		unsigned char *hdr;
		unsigned char len = skb->len;

		hdr = skb_push(skb, NFCMRVL_HCI_EVENT_HEADER_SIZE);
		hdr[0] = NFCMRVL_HCI_COMMAND_CODE;
		hdr[1] = NFCMRVL_HCI_OGF;
		hdr[2] = NFCMRVL_HCI_OCF;
		hdr[3] = len;
	}

	return priv->if_ops->nci_send(priv, skb);
}