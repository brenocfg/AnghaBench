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
struct bt3c_info {int /*<<< orphan*/  txq; } ;

/* Variables and functions */
 struct bt3c_info* hci_get_drvdata (struct hci_dev*) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bt3c_hci_flush(struct hci_dev *hdev)
{
	struct bt3c_info *info = hci_get_drvdata(hdev);

	/* Drop TX queue */
	skb_queue_purge(&(info->txq));

	return 0;
}