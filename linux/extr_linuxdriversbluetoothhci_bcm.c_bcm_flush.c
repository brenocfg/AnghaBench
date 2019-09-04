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
struct hci_uart {int /*<<< orphan*/  hdev; struct bcm_data* priv; } ;
struct bcm_data {int /*<<< orphan*/  txq; } ;

/* Variables and functions */
 int /*<<< orphan*/  bt_dev_dbg (int /*<<< orphan*/ ,char*,struct hci_uart*) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bcm_flush(struct hci_uart *hu)
{
	struct bcm_data *bcm = hu->priv;

	bt_dev_dbg(hu->hdev, "hu %p", hu);

	skb_queue_purge(&bcm->txq);

	return 0;
}