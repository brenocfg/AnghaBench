#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct hns3_nic_priv {int vector_num; TYPE_3__* ae_handle; int /*<<< orphan*/ * tqp_vector; } ;
struct TYPE_6__ {int num_tqps; int /*<<< orphan*/ * tqp; } ;
struct hnae3_handle {TYPE_1__ kinfo; } ;
struct hnae3_ae_ops {int /*<<< orphan*/  (* stop ) (TYPE_3__*) ;} ;
struct TYPE_8__ {TYPE_2__* ae_algo; } ;
struct TYPE_7__ {struct hnae3_ae_ops* ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  hns3_clear_all_ring (TYPE_3__*,int) ; 
 int /*<<< orphan*/  hns3_free_rx_cpu_rmap (struct net_device*) ; 
 struct hnae3_handle* hns3_get_handle (struct net_device*) ; 
 int /*<<< orphan*/  hns3_nic_resetting (struct net_device*) ; 
 int /*<<< orphan*/  hns3_nic_uninit_irq (struct hns3_nic_priv*) ; 
 int /*<<< orphan*/  hns3_reset_tx_queue (TYPE_3__*) ; 
 int /*<<< orphan*/  hns3_tqp_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns3_vector_disable (int /*<<< orphan*/ *) ; 
 struct hns3_nic_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

__attribute__((used)) static void hns3_nic_net_down(struct net_device *netdev)
{
	struct hns3_nic_priv *priv = netdev_priv(netdev);
	struct hnae3_handle *h = hns3_get_handle(netdev);
	const struct hnae3_ae_ops *ops;
	int i;

	/* disable vectors */
	for (i = 0; i < priv->vector_num; i++)
		hns3_vector_disable(&priv->tqp_vector[i]);

	/* disable rcb */
	for (i = 0; i < h->kinfo.num_tqps; i++)
		hns3_tqp_disable(h->kinfo.tqp[i]);

	/* stop ae_dev */
	ops = priv->ae_handle->ae_algo->ops;
	if (ops->stop)
		ops->stop(priv->ae_handle);

	hns3_free_rx_cpu_rmap(netdev);

	/* free irq resources */
	hns3_nic_uninit_irq(priv);

	/* delay ring buffer clearing to hns3_reset_notify_uninit_enet
	 * during reset process, because driver may not be able
	 * to disable the ring through firmware when downing the netdev.
	 */
	if (!hns3_nic_resetting(netdev))
		hns3_clear_all_ring(priv->ae_handle, false);

	hns3_reset_tx_queue(priv->ae_handle);
}