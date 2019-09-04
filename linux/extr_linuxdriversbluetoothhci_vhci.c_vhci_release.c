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
struct vhci_data {int /*<<< orphan*/  readq; struct hci_dev* hdev; int /*<<< orphan*/  open_timeout; } ;
struct inode {int dummy; } ;
struct hci_dev {int dummy; } ;
struct file {struct vhci_data* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_free_dev (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_unregister_dev (struct hci_dev*) ; 
 int /*<<< orphan*/  kfree (struct vhci_data*) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vhci_release(struct inode *inode, struct file *file)
{
	struct vhci_data *data = file->private_data;
	struct hci_dev *hdev;

	cancel_delayed_work_sync(&data->open_timeout);

	hdev = data->hdev;

	if (hdev) {
		hci_unregister_dev(hdev);
		hci_free_dev(hdev);
	}

	skb_queue_purge(&data->readq);
	file->private_data = NULL;
	kfree(data);

	return 0;
}