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
struct hci_dev {int dummy; } ;
struct bfusb_data {int /*<<< orphan*/  transmit_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct hci_dev*,struct bfusb_data*) ; 
 struct bfusb_data* hci_get_drvdata (struct hci_dev*) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bfusb_flush(struct hci_dev *hdev)
{
	struct bfusb_data *data = hci_get_drvdata(hdev);

	BT_DBG("hdev %p bfusb %p", hdev, data);

	skb_queue_purge(&data->transmit_q);

	return 0;
}