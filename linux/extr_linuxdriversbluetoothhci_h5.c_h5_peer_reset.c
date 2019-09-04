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
struct hci_uart {int /*<<< orphan*/  hdev; struct h5* priv; } ;
struct h5 {scalar_t__ tx_ack; scalar_t__ tx_seq; int /*<<< orphan*/  unack; int /*<<< orphan*/  unrel; int /*<<< orphan*/  rel; int /*<<< orphan*/  timer; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_ERR (char*) ; 
 int /*<<< orphan*/  H5_UNINITIALIZED ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_reset_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void h5_peer_reset(struct hci_uart *hu)
{
	struct h5 *h5 = hu->priv;

	BT_ERR("Peer device has reset");

	h5->state = H5_UNINITIALIZED;

	del_timer(&h5->timer);

	skb_queue_purge(&h5->rel);
	skb_queue_purge(&h5->unrel);
	skb_queue_purge(&h5->unack);

	h5->tx_seq = 0;
	h5->tx_ack = 0;

	/* Send reset request to upper stack */
	hci_reset_dev(hu->hdev);
}