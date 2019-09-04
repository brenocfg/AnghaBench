#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct hns3_nic_priv {int vector_num; int /*<<< orphan*/ * tqp_vector; int /*<<< orphan*/  state; struct hnae3_handle* ae_handle; } ;
struct hnae3_handle {TYPE_2__* ae_algo; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* start ) (struct hnae3_handle*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HNS3_NIC_STATE_DOWN ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int hns3_nic_init_irq (struct hns3_nic_priv*) ; 
 int hns3_nic_reset_all_ring (struct hnae3_handle*) ; 
 int /*<<< orphan*/  hns3_nic_uninit_irq (struct hns3_nic_priv*) ; 
 int /*<<< orphan*/  hns3_vector_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hns3_vector_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int) ; 
 struct hns3_nic_priv* netdev_priv (struct net_device*) ; 
 int stub1 (struct hnae3_handle*) ; 

__attribute__((used)) static int hns3_nic_net_up(struct net_device *netdev)
{
	struct hns3_nic_priv *priv = netdev_priv(netdev);
	struct hnae3_handle *h = priv->ae_handle;
	int i, j;
	int ret;

	ret = hns3_nic_reset_all_ring(h);
	if (ret)
		return ret;

	/* get irq resource for all vectors */
	ret = hns3_nic_init_irq(priv);
	if (ret) {
		netdev_err(netdev, "hns init irq failed! ret=%d\n", ret);
		return ret;
	}

	/* enable the vectors */
	for (i = 0; i < priv->vector_num; i++)
		hns3_vector_enable(&priv->tqp_vector[i]);

	/* start the ae_dev */
	ret = h->ae_algo->ops->start ? h->ae_algo->ops->start(h) : 0;
	if (ret)
		goto out_start_err;

	clear_bit(HNS3_NIC_STATE_DOWN, &priv->state);

	return 0;

out_start_err:
	for (j = i - 1; j >= 0; j--)
		hns3_vector_disable(&priv->tqp_vector[j]);

	hns3_nic_uninit_irq(priv);

	return ret;
}