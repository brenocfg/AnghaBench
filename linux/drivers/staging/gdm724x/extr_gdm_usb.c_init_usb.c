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
struct usb_tx_sdu {int /*<<< orphan*/  list; } ;
struct usb_rx {int /*<<< orphan*/  free_list; } ;
struct tx_cxt {scalar_t__ avail_count; int /*<<< orphan*/  free_list; int /*<<< orphan*/  lock; int /*<<< orphan*/  hci_list; int /*<<< orphan*/  sdu_list; } ;
struct rx_cxt {scalar_t__ avail_count; int /*<<< orphan*/  free_list; int /*<<< orphan*/  to_host_lock; int /*<<< orphan*/  submit_lock; int /*<<< orphan*/  rx_lock; int /*<<< orphan*/  to_host_list; int /*<<< orphan*/  rx_submit_list; } ;
struct lte_udev {int send_complete; int /*<<< orphan*/  work_rx; int /*<<< orphan*/  work_tx; int /*<<< orphan*/ * rx_cb; int /*<<< orphan*/  usb_state; scalar_t__ request_mac_addr; scalar_t__ tx_stop; struct rx_cxt rx; struct tx_cxt tx; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int MAX_NUM_SDU_BUF ; 
 int MAX_RX_SUBMIT_COUNT ; 
 int /*<<< orphan*/  PM_NORMAL ; 
 struct usb_rx* alloc_rx_struct () ; 
 struct usb_tx_sdu* alloc_tx_sdu_struct () ; 
 int /*<<< orphan*/  do_rx ; 
 int /*<<< orphan*/  do_tx ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_usb (struct lte_udev*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int init_usb(struct lte_udev *udev)
{
	int ret = 0;
	int i;
	struct tx_cxt *tx = &udev->tx;
	struct rx_cxt *rx = &udev->rx;
	struct usb_tx_sdu *t_sdu = NULL;
	struct usb_rx *r = NULL;

	udev->send_complete = 1;
	udev->tx_stop = 0;
	udev->request_mac_addr = 0;
	udev->usb_state = PM_NORMAL;

	INIT_LIST_HEAD(&tx->sdu_list);
	INIT_LIST_HEAD(&tx->hci_list);
	INIT_LIST_HEAD(&tx->free_list);
	INIT_LIST_HEAD(&rx->rx_submit_list);
	INIT_LIST_HEAD(&rx->free_list);
	INIT_LIST_HEAD(&rx->to_host_list);
	spin_lock_init(&tx->lock);
	spin_lock_init(&rx->rx_lock);
	spin_lock_init(&rx->submit_lock);
	spin_lock_init(&rx->to_host_lock);

	tx->avail_count = 0;
	rx->avail_count = 0;

	udev->rx_cb = NULL;

	for (i = 0; i < MAX_NUM_SDU_BUF; i++) {
		t_sdu = alloc_tx_sdu_struct();
		if (!t_sdu) {
			ret = -ENOMEM;
			goto fail;
		}

		list_add(&t_sdu->list, &tx->free_list);
		tx->avail_count++;
	}

	for (i = 0; i < MAX_RX_SUBMIT_COUNT * 2; i++) {
		r = alloc_rx_struct();
		if (!r) {
			ret = -ENOMEM;
			goto fail;
		}

		list_add(&r->free_list, &rx->free_list);
		rx->avail_count++;
	}
	INIT_DELAYED_WORK(&udev->work_tx, do_tx);
	INIT_DELAYED_WORK(&udev->work_rx, do_rx);
	return 0;
fail:
	release_usb(udev);
	return ret;
}