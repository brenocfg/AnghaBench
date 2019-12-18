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
struct net_device {int /*<<< orphan*/  rx_cpu_rmap; } ;
struct hns3_nic_priv {int vector_num; struct hns3_enet_tqp_vector* tqp_vector; } ;
struct hns3_enet_tqp_vector {int /*<<< orphan*/  vector_irq; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  alloc_irq_cpu_rmap (int) ; 
 int /*<<< orphan*/  hns3_free_rx_cpu_rmap (struct net_device*) ; 
 int irq_cpu_rmap_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hns3_nic_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int hns3_set_rx_cpu_rmap(struct net_device *netdev)
{
#ifdef CONFIG_RFS_ACCEL
	struct hns3_nic_priv *priv = netdev_priv(netdev);
	struct hns3_enet_tqp_vector *tqp_vector;
	int i, ret;

	if (!netdev->rx_cpu_rmap) {
		netdev->rx_cpu_rmap = alloc_irq_cpu_rmap(priv->vector_num);
		if (!netdev->rx_cpu_rmap)
			return -ENOMEM;
	}

	for (i = 0; i < priv->vector_num; i++) {
		tqp_vector = &priv->tqp_vector[i];
		ret = irq_cpu_rmap_add(netdev->rx_cpu_rmap,
				       tqp_vector->vector_irq);
		if (ret) {
			hns3_free_rx_cpu_rmap(netdev);
			return ret;
		}
	}
#endif
	return 0;
}