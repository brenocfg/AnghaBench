#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nokia_bt_dev {int /*<<< orphan*/ * rx_skb; TYPE_1__* serdev; } ;
struct hci_uart {int /*<<< orphan*/  hdev; int /*<<< orphan*/  flags; struct nokia_bt_dev* priv; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EUNATCH ; 
 int /*<<< orphan*/  HCI_UART_REGISTERED ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/ * h4_recv_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nokia_recv_pkts ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nokia_recv(struct hci_uart *hu, const void *data, int count)
{
	struct nokia_bt_dev *btdev = hu->priv;
	struct device *dev = &btdev->serdev->dev;
	int err;

	if (!test_bit(HCI_UART_REGISTERED, &hu->flags))
		return -EUNATCH;

	btdev->rx_skb = h4_recv_buf(hu->hdev, btdev->rx_skb, data, count,
				  nokia_recv_pkts, ARRAY_SIZE(nokia_recv_pkts));
	if (IS_ERR(btdev->rx_skb)) {
		err = PTR_ERR(btdev->rx_skb);
		dev_err(dev, "Frame reassembly failed (%d)", err);
		btdev->rx_skb = NULL;
		return err;
	}

	return count;
}