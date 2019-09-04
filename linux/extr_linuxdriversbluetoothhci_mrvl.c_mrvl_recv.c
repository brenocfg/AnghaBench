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
struct mrvl_data {int /*<<< orphan*/ * rx_skb; } ;
struct hci_uart {int /*<<< orphan*/  hdev; int /*<<< orphan*/  flags; struct mrvl_data* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EUNATCH ; 
 int /*<<< orphan*/  HCI_UART_REGISTERED ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bt_dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * h4_recv_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrvl_recv_pkts ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mrvl_recv(struct hci_uart *hu, const void *data, int count)
{
	struct mrvl_data *mrvl = hu->priv;

	if (!test_bit(HCI_UART_REGISTERED, &hu->flags))
		return -EUNATCH;

	mrvl->rx_skb = h4_recv_buf(hu->hdev, mrvl->rx_skb, data, count,
				    mrvl_recv_pkts,
				    ARRAY_SIZE(mrvl_recv_pkts));
	if (IS_ERR(mrvl->rx_skb)) {
		int err = PTR_ERR(mrvl->rx_skb);
		bt_dev_err(hu->hdev, "Frame reassembly failed (%d)", err);
		mrvl->rx_skb = NULL;
		return err;
	}

	return count;
}