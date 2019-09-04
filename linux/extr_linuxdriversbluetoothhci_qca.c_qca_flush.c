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
struct qca_data {int /*<<< orphan*/  txq; int /*<<< orphan*/  tx_wait_q; } ;
struct hci_uart {struct qca_data* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct hci_uart*) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qca_flush(struct hci_uart *hu)
{
	struct qca_data *qca = hu->priv;

	BT_DBG("hu %p qca flush", hu);

	skb_queue_purge(&qca->tx_wait_q);
	skb_queue_purge(&qca->txq);

	return 0;
}