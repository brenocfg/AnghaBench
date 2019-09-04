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
struct hci_uart {struct ag6xx_data* priv; } ;
struct ag6xx_data {int /*<<< orphan*/  rx_skb; int /*<<< orphan*/  txq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct hci_uart*) ; 
 int /*<<< orphan*/  kfree (struct ag6xx_data*) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ag6xx_close(struct hci_uart *hu)
{
	struct ag6xx_data *ag6xx = hu->priv;

	BT_DBG("hu %p", hu);

	skb_queue_purge(&ag6xx->txq);
	kfree_skb(ag6xx->rx_skb);
	kfree(ag6xx);

	hu->priv = NULL;
	return 0;
}