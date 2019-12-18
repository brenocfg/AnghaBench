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
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/ * data; } ;
struct microread_info {int async_cb_type; int /*<<< orphan*/  async_cb_context; int /*<<< orphan*/  (* async_cb ) (int /*<<< orphan*/ ,struct sk_buff*,int) ;} ;

/* Variables and functions */
 int EPROTO ; 
#define  MICROREAD_CB_TYPE_READER_ALL 128 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int nfc_hci_result_to_errno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct sk_buff*,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,struct sk_buff*,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,struct sk_buff*,int) ; 

__attribute__((used)) static void microread_im_transceive_cb(void *context, struct sk_buff *skb,
				       int err)
{
	struct microread_info *info = context;

	switch (info->async_cb_type) {
	case MICROREAD_CB_TYPE_READER_ALL:
		if (err == 0) {
			if (skb->len == 0) {
				err = -EPROTO;
				kfree_skb(skb);
				info->async_cb(info->async_cb_context, NULL,
					       -EPROTO);
				return;
			}

			if (skb->data[skb->len - 1] != 0) {
				err = nfc_hci_result_to_errno(
						       skb->data[skb->len - 1]);
				kfree_skb(skb);
				info->async_cb(info->async_cb_context, NULL,
					       err);
				return;
			}

			skb_trim(skb, skb->len - 1);	/* RF Error ind. */
		}
		info->async_cb(info->async_cb_context, skb, err);
		break;
	default:
		if (err == 0)
			kfree_skb(skb);
		break;
	}
}