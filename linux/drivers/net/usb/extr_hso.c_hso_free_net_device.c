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
struct hso_net {scalar_t__ net; struct hso_device* mux_bulk_tx_buf; int /*<<< orphan*/  mux_bulk_tx_urb; struct hso_device** mux_bulk_rx_buf_pool; int /*<<< orphan*/ * mux_bulk_rx_urb_pool; int /*<<< orphan*/  parent; } ;
struct hso_device {int dummy; } ;

/* Variables and functions */
 int MUX_BULK_RX_BUF_COUNT ; 
 struct hso_net* dev2net (struct hso_device*) ; 
 int /*<<< orphan*/  free_netdev (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct hso_device*) ; 
 int /*<<< orphan*/  remove_net_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_netdev (scalar_t__) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hso_free_net_device(struct hso_device *hso_dev)
{
	int i;
	struct hso_net *hso_net = dev2net(hso_dev);

	if (!hso_net)
		return;

	remove_net_device(hso_net->parent);

	if (hso_net->net)
		unregister_netdev(hso_net->net);

	/* start freeing */
	for (i = 0; i < MUX_BULK_RX_BUF_COUNT; i++) {
		usb_free_urb(hso_net->mux_bulk_rx_urb_pool[i]);
		kfree(hso_net->mux_bulk_rx_buf_pool[i]);
		hso_net->mux_bulk_rx_buf_pool[i] = NULL;
	}
	usb_free_urb(hso_net->mux_bulk_tx_urb);
	kfree(hso_net->mux_bulk_tx_buf);
	hso_net->mux_bulk_tx_buf = NULL;

	if (hso_net->net)
		free_netdev(hso_net->net);

	kfree(hso_dev);
}