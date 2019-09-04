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
struct intel_data {int /*<<< orphan*/ * rx_skb; } ;
struct hci_uart {int /*<<< orphan*/  hdev; int /*<<< orphan*/  flags; struct intel_data* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EUNATCH ; 
 int /*<<< orphan*/  HCI_UART_REGISTERED ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bt_dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * h4_recv_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_recv_pkts ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int intel_recv(struct hci_uart *hu, const void *data, int count)
{
	struct intel_data *intel = hu->priv;

	if (!test_bit(HCI_UART_REGISTERED, &hu->flags))
		return -EUNATCH;

	intel->rx_skb = h4_recv_buf(hu->hdev, intel->rx_skb, data, count,
				    intel_recv_pkts,
				    ARRAY_SIZE(intel_recv_pkts));
	if (IS_ERR(intel->rx_skb)) {
		int err = PTR_ERR(intel->rx_skb);
		bt_dev_err(hu->hdev, "Frame reassembly failed (%d)", err);
		intel->rx_skb = NULL;
		return err;
	}

	return count;
}