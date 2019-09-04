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
struct sk_buff {int len; } ;
struct rtl_download_response {int dummy; } ;
struct rtl_download_cmd {int index; int /*<<< orphan*/  data; } ;
struct hci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int,int) ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HCI_INIT_TIMEOUT ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int PTR_ERR (struct sk_buff*) ; 
 int RTL_FRAG_LEN ; 
 struct sk_buff* __hci_cmd_sync (struct hci_dev*,int,int,struct rtl_download_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct rtl_download_cmd*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct rtl_download_cmd* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char const*,int) ; 
 int /*<<< orphan*/  rtl_dev_err (struct hci_dev*,char*,...) ; 

__attribute__((used)) static int rtl_download_firmware(struct hci_dev *hdev,
				 const unsigned char *data, int fw_len)
{
	struct rtl_download_cmd *dl_cmd;
	int frag_num = fw_len / RTL_FRAG_LEN + 1;
	int frag_len = RTL_FRAG_LEN;
	int ret = 0;
	int i;

	dl_cmd = kmalloc(sizeof(struct rtl_download_cmd), GFP_KERNEL);
	if (!dl_cmd)
		return -ENOMEM;

	for (i = 0; i < frag_num; i++) {
		struct sk_buff *skb;

		BT_DBG("download fw (%d/%d)", i, frag_num);

		dl_cmd->index = i;
		if (i == (frag_num - 1)) {
			dl_cmd->index |= 0x80; /* data end */
			frag_len = fw_len % RTL_FRAG_LEN;
		}
		memcpy(dl_cmd->data, data, frag_len);

		/* Send download command */
		skb = __hci_cmd_sync(hdev, 0xfc20, frag_len + 1, dl_cmd,
				     HCI_INIT_TIMEOUT);
		if (IS_ERR(skb)) {
			rtl_dev_err(hdev, "download fw command failed (%ld)\n",
				    PTR_ERR(skb));
			ret = -PTR_ERR(skb);
			goto out;
		}

		if (skb->len != sizeof(struct rtl_download_response)) {
			rtl_dev_err(hdev, "download fw event length mismatch\n");
			kfree_skb(skb);
			ret = -EIO;
			goto out;
		}

		kfree_skb(skb);
		data += RTL_FRAG_LEN;
	}

out:
	kfree(dl_cmd);
	return ret;
}