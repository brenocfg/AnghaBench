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
struct btmtkuart_dev {int stp_cursor; scalar_t__ stp_dlen; int /*<<< orphan*/ * rx_skb; int /*<<< orphan*/  tx_work; int /*<<< orphan*/  txq; int /*<<< orphan*/  serdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 struct btmtkuart_dev* hci_get_drvdata (struct hci_dev*) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serdev_device_write_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int btmtkuart_flush(struct hci_dev *hdev)
{
	struct btmtkuart_dev *bdev = hci_get_drvdata(hdev);

	/* Flush any pending characters */
	serdev_device_write_flush(bdev->serdev);
	skb_queue_purge(&bdev->txq);

	cancel_work_sync(&bdev->tx_work);

	kfree_skb(bdev->rx_skb);
	bdev->rx_skb = NULL;

	bdev->stp_cursor = 2;
	bdev->stp_dlen = 0;

	return 0;
}