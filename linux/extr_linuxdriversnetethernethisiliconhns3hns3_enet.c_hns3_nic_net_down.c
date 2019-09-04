#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct hns3_nic_priv {int vector_num; TYPE_2__* ae_handle; int /*<<< orphan*/ * tqp_vector; int /*<<< orphan*/  state; } ;
struct hnae3_ae_ops {int /*<<< orphan*/  (* stop ) (TYPE_2__*) ;} ;
struct TYPE_5__ {TYPE_1__* ae_algo; } ;
struct TYPE_4__ {struct hnae3_ae_ops* ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  HNS3_NIC_STATE_DOWN ; 
 int /*<<< orphan*/  hns3_clear_all_ring (TYPE_2__*) ; 
 int /*<<< orphan*/  hns3_nic_uninit_irq (struct hns3_nic_priv*) ; 
 int /*<<< orphan*/  hns3_vector_disable (int /*<<< orphan*/ *) ; 
 struct hns3_nic_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hns3_nic_net_down(struct net_device *netdev)
{
	struct hns3_nic_priv *priv = netdev_priv(netdev);
	const struct hnae3_ae_ops *ops;
	int i;

	if (test_and_set_bit(HNS3_NIC_STATE_DOWN, &priv->state))
		return;

	/* disable vectors */
	for (i = 0; i < priv->vector_num; i++)
		hns3_vector_disable(&priv->tqp_vector[i]);

	/* stop ae_dev */
	ops = priv->ae_handle->ae_algo->ops;
	if (ops->stop)
		ops->stop(priv->ae_handle);

	/* free irq resources */
	hns3_nic_uninit_irq(priv);

	hns3_clear_all_ring(priv->ae_handle);
}