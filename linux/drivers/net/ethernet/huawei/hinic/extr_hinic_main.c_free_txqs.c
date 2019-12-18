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
struct net_device {int /*<<< orphan*/  dev; } ;
struct hinic_dev {int /*<<< orphan*/ * txqs; struct net_device* netdev; int /*<<< orphan*/  hwdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hinic_clean_txq (int /*<<< orphan*/ *) ; 
 int hinic_hwdev_num_qps (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_txqs(struct hinic_dev *nic_dev)
{
	int i, num_txqs = hinic_hwdev_num_qps(nic_dev->hwdev);
	struct net_device *netdev = nic_dev->netdev;

	if (!nic_dev->txqs)
		return;

	for (i = 0; i < num_txqs; i++)
		hinic_clean_txq(&nic_dev->txqs[i]);

	devm_kfree(&netdev->dev, nic_dev->txqs);
	nic_dev->txqs = NULL;
}