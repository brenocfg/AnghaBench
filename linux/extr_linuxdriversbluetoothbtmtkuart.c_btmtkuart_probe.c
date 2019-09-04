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
struct serdev_device {int /*<<< orphan*/  dev; } ;
struct hci_dev {int manufacturer; int /*<<< orphan*/  quirks; int /*<<< orphan*/  send; int /*<<< orphan*/  shutdown; int /*<<< orphan*/  setup; int /*<<< orphan*/  flush; int /*<<< orphan*/  close; int /*<<< orphan*/  open; int /*<<< orphan*/  bus; } ;
struct btmtkuart_dev {struct hci_dev* hdev; int /*<<< orphan*/  txq; int /*<<< orphan*/  tx_work; struct serdev_device* serdev; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HCI_QUIRK_NON_PERSISTENT_SETUP ; 
 int /*<<< orphan*/  HCI_UART ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_HCIDEV_DEV (struct hci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btmtkuart_client_ops ; 
 int /*<<< orphan*/  btmtkuart_close ; 
 int /*<<< orphan*/  btmtkuart_flush ; 
 int /*<<< orphan*/  btmtkuart_open ; 
 int /*<<< orphan*/  btmtkuart_send_frame ; 
 int /*<<< orphan*/  btmtkuart_setup ; 
 int /*<<< orphan*/  btmtkuart_shutdown ; 
 int /*<<< orphan*/  btmtkuart_tx_work ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 struct btmtkuart_dev* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct hci_dev* hci_alloc_dev () ; 
 int /*<<< orphan*/  hci_free_dev (struct hci_dev*) ; 
 scalar_t__ hci_register_dev (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_set_drvdata (struct hci_dev*,struct btmtkuart_dev*) ; 
 int /*<<< orphan*/  serdev_device_set_client_ops (struct serdev_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serdev_device_set_drvdata (struct serdev_device*,struct btmtkuart_dev*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int btmtkuart_probe(struct serdev_device *serdev)
{
	struct btmtkuart_dev *bdev;
	struct hci_dev *hdev;

	bdev = devm_kzalloc(&serdev->dev, sizeof(*bdev), GFP_KERNEL);
	if (!bdev)
		return -ENOMEM;

	bdev->clk = devm_clk_get(&serdev->dev, "ref");
	if (IS_ERR(bdev->clk))
		return PTR_ERR(bdev->clk);

	bdev->serdev = serdev;
	serdev_device_set_drvdata(serdev, bdev);

	serdev_device_set_client_ops(serdev, &btmtkuart_client_ops);

	INIT_WORK(&bdev->tx_work, btmtkuart_tx_work);
	skb_queue_head_init(&bdev->txq);

	/* Initialize and register HCI device */
	hdev = hci_alloc_dev();
	if (!hdev) {
		dev_err(&serdev->dev, "Can't allocate HCI device\n");
		return -ENOMEM;
	}

	bdev->hdev = hdev;

	hdev->bus = HCI_UART;
	hci_set_drvdata(hdev, bdev);

	hdev->open     = btmtkuart_open;
	hdev->close    = btmtkuart_close;
	hdev->flush    = btmtkuart_flush;
	hdev->setup    = btmtkuart_setup;
	hdev->shutdown = btmtkuart_shutdown;
	hdev->send     = btmtkuart_send_frame;
	SET_HCIDEV_DEV(hdev, &serdev->dev);

	hdev->manufacturer = 70;
	set_bit(HCI_QUIRK_NON_PERSISTENT_SETUP, &hdev->quirks);

	if (hci_register_dev(hdev) < 0) {
		dev_err(&serdev->dev, "Can't register HCI device\n");
		hci_free_dev(hdev);
		return -ENODEV;
	}

	return 0;
}