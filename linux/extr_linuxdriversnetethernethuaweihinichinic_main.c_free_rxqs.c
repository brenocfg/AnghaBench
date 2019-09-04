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
struct hinic_dev {int /*<<< orphan*/ * rxqs; struct net_device* netdev; int /*<<< orphan*/  hwdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hinic_clean_rxq (int /*<<< orphan*/ *) ; 
 int hinic_hwdev_num_qps (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_rxqs(struct hinic_dev *nic_dev)
{
	int i, num_rxqs = hinic_hwdev_num_qps(nic_dev->hwdev);
	struct net_device *netdev = nic_dev->netdev;

	if (!nic_dev->rxqs)
		return;

	for (i = 0; i < num_rxqs; i++)
		hinic_clean_rxq(&nic_dev->rxqs[i]);

	devm_kfree(&netdev->dev, nic_dev->rxqs);
	nic_dev->rxqs = NULL;
}