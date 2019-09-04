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
struct hci_dev {int /*<<< orphan*/  send; int /*<<< orphan*/  flush; int /*<<< orphan*/  close; int /*<<< orphan*/  open; int /*<<< orphan*/  bus; } ;
struct firmware {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct bt3c_info {struct hci_dev* hdev; TYPE_1__* p_dev; int /*<<< orphan*/ * rx_skb; scalar_t__ rx_count; int /*<<< orphan*/  rx_state; int /*<<< orphan*/  txq; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_ERR (char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HCI_PCCARD ; 
 int /*<<< orphan*/  RECV_WAIT_PACKET_TYPE ; 
 int /*<<< orphan*/  SET_HCIDEV_DEV (struct hci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bt3c_hci_close ; 
 int /*<<< orphan*/  bt3c_hci_flush ; 
 int /*<<< orphan*/  bt3c_hci_open ; 
 int /*<<< orphan*/  bt3c_hci_send_frame ; 
 int bt3c_load_firmware (struct bt3c_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hci_dev* hci_alloc_dev () ; 
 int /*<<< orphan*/  hci_free_dev (struct hci_dev*) ; 
 int hci_register_dev (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_set_drvdata (struct hci_dev*,struct bt3c_info*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bt3c_open(struct bt3c_info *info)
{
	const struct firmware *firmware;
	struct hci_dev *hdev;
	int err;

	spin_lock_init(&(info->lock));

	skb_queue_head_init(&(info->txq));

	info->rx_state = RECV_WAIT_PACKET_TYPE;
	info->rx_count = 0;
	info->rx_skb = NULL;

	/* Initialize HCI device */
	hdev = hci_alloc_dev();
	if (!hdev) {
		BT_ERR("Can't allocate HCI device");
		return -ENOMEM;
	}

	info->hdev = hdev;

	hdev->bus = HCI_PCCARD;
	hci_set_drvdata(hdev, info);
	SET_HCIDEV_DEV(hdev, &info->p_dev->dev);

	hdev->open  = bt3c_hci_open;
	hdev->close = bt3c_hci_close;
	hdev->flush = bt3c_hci_flush;
	hdev->send  = bt3c_hci_send_frame;

	/* Load firmware */
	err = request_firmware(&firmware, "BT3CPCC.bin", &info->p_dev->dev);
	if (err < 0) {
		BT_ERR("Firmware request failed");
		goto error;
	}

	err = bt3c_load_firmware(info, firmware->data, firmware->size);

	release_firmware(firmware);

	if (err < 0) {
		BT_ERR("Firmware loading failed");
		goto error;
	}

	/* Timeout before it is safe to send the first HCI packet */
	msleep(1000);

	/* Register HCI device */
	err = hci_register_dev(hdev);
	if (err < 0) {
		BT_ERR("Can't register HCI device");
		goto error;
	}

	return 0;

error:
	info->hdev = NULL;
	hci_free_dev(hdev);
	return err;
}