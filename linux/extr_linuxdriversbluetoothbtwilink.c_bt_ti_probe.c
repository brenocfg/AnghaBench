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
struct ti_st {struct hci_dev* hdev; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct hci_dev {int /*<<< orphan*/  send; int /*<<< orphan*/ * flush; int /*<<< orphan*/  close; int /*<<< orphan*/  open; int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct hci_dev*) ; 
 int /*<<< orphan*/  BT_ERR (char*,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HCI_UART ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct ti_st*) ; 
 struct ti_st* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct hci_dev* hci_alloc_dev () ; 
 int /*<<< orphan*/  hci_free_dev (struct hci_dev*) ; 
 int hci_register_dev (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_set_drvdata (struct hci_dev*,struct ti_st*) ; 
 int /*<<< orphan*/  ti_st_close ; 
 int /*<<< orphan*/  ti_st_open ; 
 int /*<<< orphan*/  ti_st_send_frame ; 

__attribute__((used)) static int bt_ti_probe(struct platform_device *pdev)
{
	struct ti_st *hst;
	struct hci_dev *hdev;
	int err;

	hst = devm_kzalloc(&pdev->dev, sizeof(struct ti_st), GFP_KERNEL);
	if (!hst)
		return -ENOMEM;

	/* Expose "hciX" device to user space */
	hdev = hci_alloc_dev();
	if (!hdev)
		return -ENOMEM;

	BT_DBG("hdev %p", hdev);

	hst->hdev = hdev;
	hdev->bus = HCI_UART;
	hci_set_drvdata(hdev, hst);
	hdev->open = ti_st_open;
	hdev->close = ti_st_close;
	hdev->flush = NULL;
	hdev->send = ti_st_send_frame;

	err = hci_register_dev(hdev);
	if (err < 0) {
		BT_ERR("Can't register HCI device error %d", err);
		hci_free_dev(hdev);
		return err;
	}

	BT_DBG("HCI device registered (hdev %p)", hdev);

	dev_set_drvdata(&pdev->dev, hst);
	return 0;
}