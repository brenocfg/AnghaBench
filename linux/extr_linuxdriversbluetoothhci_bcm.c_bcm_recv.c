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
struct hci_uart {int /*<<< orphan*/  hdev; int /*<<< orphan*/  flags; struct bcm_data* priv; } ;
struct bcm_data {TYPE_1__* dev; int /*<<< orphan*/ * rx_skb; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EUNATCH ; 
 int /*<<< orphan*/  HCI_UART_REGISTERED ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ bcm_device_exists (TYPE_1__*) ; 
 int /*<<< orphan*/  bcm_device_lock ; 
 int /*<<< orphan*/  bcm_recv_pkts ; 
 int /*<<< orphan*/  bt_dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * h4_recv_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bcm_recv(struct hci_uart *hu, const void *data, int count)
{
	struct bcm_data *bcm = hu->priv;

	if (!test_bit(HCI_UART_REGISTERED, &hu->flags))
		return -EUNATCH;

	bcm->rx_skb = h4_recv_buf(hu->hdev, bcm->rx_skb, data, count,
				  bcm_recv_pkts, ARRAY_SIZE(bcm_recv_pkts));
	if (IS_ERR(bcm->rx_skb)) {
		int err = PTR_ERR(bcm->rx_skb);
		bt_dev_err(hu->hdev, "Frame reassembly failed (%d)", err);
		bcm->rx_skb = NULL;
		return err;
	} else if (!bcm->rx_skb) {
		/* Delay auto-suspend when receiving completed packet */
		mutex_lock(&bcm_device_lock);
		if (bcm->dev && bcm_device_exists(bcm->dev)) {
			pm_runtime_get(bcm->dev->dev);
			pm_runtime_mark_last_busy(bcm->dev->dev);
			pm_runtime_put_autosuspend(bcm->dev->dev);
		}
		mutex_unlock(&bcm_device_lock);
	}

	return count;
}