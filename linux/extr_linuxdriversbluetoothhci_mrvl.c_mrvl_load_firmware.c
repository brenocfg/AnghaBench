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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct mrvl_data {int tx_len; int /*<<< orphan*/  rawq; int /*<<< orphan*/  flags; } ;
struct hci_uart {struct mrvl_data* priv; } ;
struct hci_dev {int /*<<< orphan*/  dev; } ;
struct firmware {int size; int /*<<< orphan*/ * data; } ;
struct TYPE_2__ {int /*<<< orphan*/  pkt_type; } ;

/* Variables and functions */
 int EINTR ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MRVL_RAW_DATA ; 
 int /*<<< orphan*/  STATE_FW_REQ_PENDING ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 TYPE_1__* bt_cb (struct sk_buff*) ; 
 int /*<<< orphan*/  bt_dev_dbg (struct hci_dev*,char*,int) ; 
 int /*<<< orphan*/  bt_dev_err (struct hci_dev*,char*,...) ; 
 int /*<<< orphan*/  bt_dev_info (struct hci_dev*,char*,...) ; 
 struct sk_buff* bt_skb_alloc (int,int /*<<< orphan*/ ) ; 
 struct hci_uart* hci_get_drvdata (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_uart_tx_wakeup (struct hci_uart*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int wait_on_bit_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mrvl_load_firmware(struct hci_dev *hdev, const char *name)
{
	struct hci_uart *hu = hci_get_drvdata(hdev);
	struct mrvl_data *mrvl = hu->priv;
	const struct firmware *fw = NULL;
	const u8 *fw_ptr, *fw_max;
	int err;

	err = request_firmware(&fw, name, &hdev->dev);
	if (err < 0) {
		bt_dev_err(hdev, "Failed to load firmware file %s", name);
		return err;
	}

	fw_ptr = fw->data;
	fw_max = fw->data + fw->size;

	bt_dev_info(hdev, "Loading %s", name);

	set_bit(STATE_FW_REQ_PENDING, &mrvl->flags);

	while (fw_ptr <= fw_max) {
		struct sk_buff *skb;

		/* Controller drives the firmware load by sending firmware
		 * request packets containing the expected fragment size.
		 */
		err = wait_on_bit_timeout(&mrvl->flags, STATE_FW_REQ_PENDING,
					  TASK_INTERRUPTIBLE,
					  msecs_to_jiffies(2000));
		if (err == 1) {
			bt_dev_err(hdev, "Firmware load interrupted");
			err = -EINTR;
			break;
		} else if (err) {
			bt_dev_err(hdev, "Firmware request timeout");
			err = -ETIMEDOUT;
			break;
		}

		bt_dev_dbg(hdev, "Firmware request, expecting %d bytes",
			   mrvl->tx_len);

		if (fw_ptr == fw_max) {
			/* Controller requests a null size once firmware is
			 * fully loaded. If controller expects more data, there
			 * is an issue.
			 */
			if (!mrvl->tx_len) {
				bt_dev_info(hdev, "Firmware loading complete");
			} else {
				bt_dev_err(hdev, "Firmware loading failure");
				err = -EINVAL;
			}
			break;
		}

		if (fw_ptr + mrvl->tx_len > fw_max) {
			mrvl->tx_len = fw_max - fw_ptr;
			bt_dev_dbg(hdev, "Adjusting tx_len to %d",
				   mrvl->tx_len);
		}

		skb = bt_skb_alloc(mrvl->tx_len, GFP_KERNEL);
		if (!skb) {
			bt_dev_err(hdev, "Failed to alloc mem for FW packet");
			err = -ENOMEM;
			break;
		}
		bt_cb(skb)->pkt_type = MRVL_RAW_DATA;

		skb_put_data(skb, fw_ptr, mrvl->tx_len);
		fw_ptr += mrvl->tx_len;

		set_bit(STATE_FW_REQ_PENDING, &mrvl->flags);

		skb_queue_tail(&mrvl->rawq, skb);
		hci_uart_tx_wakeup(hu);
	}

	release_firmware(fw);
	return err;
}