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
struct hci_dev {int /*<<< orphan*/  name; } ;
struct btusb_data {scalar_t__ sco_num; int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  SCO_LINK ; 
 scalar_t__ hci_conn_num (struct hci_dev*,int /*<<< orphan*/ ) ; 
 struct btusb_data* hci_get_drvdata (struct hci_dev*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void btusb_notify(struct hci_dev *hdev, unsigned int evt)
{
	struct btusb_data *data = hci_get_drvdata(hdev);

	BT_DBG("%s evt %d", hdev->name, evt);

	if (hci_conn_num(hdev, SCO_LINK) != data->sco_num) {
		data->sco_num = hci_conn_num(hdev, SCO_LINK);
		schedule_work(&data->work);
	}
}