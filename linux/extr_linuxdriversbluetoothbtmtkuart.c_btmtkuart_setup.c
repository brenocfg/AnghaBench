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
typedef  int u8 ;
struct hci_dev {int dummy; } ;
typedef  int /*<<< orphan*/  param ;

/* Variables and functions */
 int /*<<< orphan*/  MTK_WMT_FUNC_CTRL ; 
 int /*<<< orphan*/  MTK_WMT_RST ; 
 int /*<<< orphan*/  bt_dev_err (struct hci_dev*,char*,int) ; 
 int mtk_hci_wmt_sync (struct hci_dev*,int /*<<< orphan*/ ,int,int,int*) ; 
 int mtk_setup_fw (struct hci_dev*) ; 

__attribute__((used)) static int btmtkuart_setup(struct hci_dev *hdev)
{
	u8 param = 0x1;
	int err = 0;

	/* Setup a firmware which the device definitely requires */
	err = mtk_setup_fw(hdev);
	if (err < 0)
		return err;

	/* Activate function the firmware providing to */
	err = mtk_hci_wmt_sync(hdev, MTK_WMT_RST, 0x4, 0, 0);
	if (err < 0) {
		bt_dev_err(hdev, "Failed to send wmt rst (%d)", err);
		return err;
	}

	/* Enable Bluetooth protocol */
	err = mtk_hci_wmt_sync(hdev, MTK_WMT_FUNC_CTRL, 0x0, sizeof(param),
			       &param);
	if (err < 0) {
		bt_dev_err(hdev, "Failed to send wmt func ctrl (%d)", err);
		return err;
	}

	return 0;
}