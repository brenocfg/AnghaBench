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
typedef  void* u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct mtk_wmt_hdr {int dir; void* flag; int /*<<< orphan*/  dlen; void* op; } ;
struct mtk_hci_wmt_cmd {int /*<<< orphan*/  data; } ;
struct hci_dev {int dummy; } ;
struct btmtkuart_dev {int /*<<< orphan*/  tx_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTMTKUART_TX_WAIT_VND_EVT ; 
 int EINTR ; 
 int EINVAL ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  HCI_INIT_TIMEOUT ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int __hci_cmd_send (struct hci_dev*,int,int,struct mtk_hci_wmt_cmd*) ; 
 int /*<<< orphan*/  bt_dev_err (struct hci_dev*,char*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 struct btmtkuart_dev* hci_get_drvdata (struct hci_dev*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int wait_on_bit_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_hci_wmt_sync(struct hci_dev *hdev, u8 op, u8 flag, u16 plen,
			    const void *param)
{
	struct btmtkuart_dev *bdev = hci_get_drvdata(hdev);
	struct mtk_hci_wmt_cmd wc;
	struct mtk_wmt_hdr *hdr;
	u32 hlen;
	int err;

	hlen = sizeof(*hdr) + plen;
	if (hlen > 255)
		return -EINVAL;

	hdr = (struct mtk_wmt_hdr *)&wc;
	hdr->dir = 1;
	hdr->op = op;
	hdr->dlen = cpu_to_le16(plen + 1);
	hdr->flag = flag;
	memcpy(wc.data, param, plen);

	set_bit(BTMTKUART_TX_WAIT_VND_EVT, &bdev->tx_state);

	err = __hci_cmd_send(hdev, 0xfc6f, hlen, &wc);
	if (err < 0) {
		clear_bit(BTMTKUART_TX_WAIT_VND_EVT, &bdev->tx_state);
		return err;
	}

	/* The vendor specific WMT commands are all answered by a vendor
	 * specific event and will not have the Command Status or Command
	 * Complete as with usual HCI command flow control.
	 *
	 * After sending the command, wait for BTMTKUART_TX_WAIT_VND_EVT
	 * state to be cleared. The driver speicfic event receive routine
	 * will clear that state and with that indicate completion of the
	 * WMT command.
	 */
	err = wait_on_bit_timeout(&bdev->tx_state, BTMTKUART_TX_WAIT_VND_EVT,
				  TASK_INTERRUPTIBLE, HCI_INIT_TIMEOUT);
	if (err == -EINTR) {
		bt_dev_err(hdev, "Execution of wmt command interrupted");
		return err;
	}

	if (err) {
		bt_dev_err(hdev, "Execution of wmt command timed out");
		return -ETIMEDOUT;
	}

	return 0;
}