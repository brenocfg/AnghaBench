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
struct intel_data {int /*<<< orphan*/  rx_skb; int /*<<< orphan*/  txq; int /*<<< orphan*/  busy_work; } ;
struct hci_uart {struct intel_data* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct hci_uart*) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_set_power (struct hci_uart*,int) ; 
 int /*<<< orphan*/  kfree (struct intel_data*) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int intel_close(struct hci_uart *hu)
{
	struct intel_data *intel = hu->priv;

	BT_DBG("hu %p", hu);

	cancel_work_sync(&intel->busy_work);

	intel_set_power(hu, false);

	skb_queue_purge(&intel->txq);
	kfree_skb(intel->rx_skb);
	kfree(intel);

	hu->priv = NULL;
	return 0;
}