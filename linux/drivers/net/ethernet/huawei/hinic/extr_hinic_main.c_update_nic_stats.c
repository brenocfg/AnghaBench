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
struct hinic_dev {int /*<<< orphan*/ * txqs; int /*<<< orphan*/ * rxqs; int /*<<< orphan*/  hwdev; } ;

/* Variables and functions */
 int hinic_hwdev_num_qps (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_rx_stats (struct hinic_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_tx_stats (struct hinic_dev*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void update_nic_stats(struct hinic_dev *nic_dev)
{
	int i, num_qps = hinic_hwdev_num_qps(nic_dev->hwdev);

	for (i = 0; i < num_qps; i++)
		update_rx_stats(nic_dev, &nic_dev->rxqs[i]);

	for (i = 0; i < num_qps; i++)
		update_tx_stats(nic_dev, &nic_dev->txqs[i]);
}