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
struct hci_dev {int dummy; } ;
struct btmrvl_private {TYPE_1__* adapter; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_queue; } ;

/* Variables and functions */
 struct btmrvl_private* hci_get_drvdata (struct hci_dev*) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int btmrvl_flush(struct hci_dev *hdev)
{
	struct btmrvl_private *priv = hci_get_drvdata(hdev);

	skb_queue_purge(&priv->adapter->tx_queue);

	return 0;
}