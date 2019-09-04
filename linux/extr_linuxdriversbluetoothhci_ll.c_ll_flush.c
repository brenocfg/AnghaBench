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
struct ll_struct {int /*<<< orphan*/  txq; int /*<<< orphan*/  tx_wait_q; } ;
struct hci_uart {struct ll_struct* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct hci_uart*) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ll_flush(struct hci_uart *hu)
{
	struct ll_struct *ll = hu->priv;

	BT_DBG("hu %p", hu);

	skb_queue_purge(&ll->tx_wait_q);
	skb_queue_purge(&ll->txq);

	return 0;
}