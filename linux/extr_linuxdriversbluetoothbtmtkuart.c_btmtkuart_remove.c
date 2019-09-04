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
struct serdev_device {int dummy; } ;
struct hci_dev {int dummy; } ;
struct btmtkuart_dev {struct hci_dev* hdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  hci_free_dev (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_unregister_dev (struct hci_dev*) ; 
 struct btmtkuart_dev* serdev_device_get_drvdata (struct serdev_device*) ; 

__attribute__((used)) static void btmtkuart_remove(struct serdev_device *serdev)
{
	struct btmtkuart_dev *bdev = serdev_device_get_drvdata(serdev);
	struct hci_dev *hdev = bdev->hdev;

	hci_unregister_dev(hdev);
	hci_free_dev(hdev);
}