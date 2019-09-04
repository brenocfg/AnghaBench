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
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int dummy; } ;
struct hns3_nic_priv {int dummy; } ;
struct hns3_enet_coalesce {int dummy; } ;
struct hnae3_handle {TYPE_2__* ae_algo; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* set_channels ) (struct hnae3_handle*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 struct hnae3_handle* hns3_get_handle (struct net_device*) ; 
 int hns3_get_ring_config (struct hns3_nic_priv*) ; 
 int hns3_init_all_ring (struct hns3_nic_priv*) ; 
 int hns3_nic_alloc_vector_data (struct hns3_nic_priv*) ; 
 int /*<<< orphan*/  hns3_nic_dealloc_vector_data (struct hns3_nic_priv*) ; 
 int hns3_nic_init_vector_data (struct hns3_nic_priv*) ; 
 int /*<<< orphan*/  hns3_nic_uninit_vector_data (struct hns3_nic_priv*) ; 
 int /*<<< orphan*/  hns3_put_ring_config (struct hns3_nic_priv*) ; 
 int /*<<< orphan*/  hns3_restore_coal (struct hns3_nic_priv*,struct hns3_enet_coalesce*,struct hns3_enet_coalesce*) ; 
 struct hns3_nic_priv* netdev_priv (struct net_device*) ; 
 int stub1 (struct hnae3_handle*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hns3_modify_tqp_num(struct net_device *netdev, u16 new_tqp_num,
			       struct hns3_enet_coalesce *tx,
			       struct hns3_enet_coalesce *rx)
{
	struct hns3_nic_priv *priv = netdev_priv(netdev);
	struct hnae3_handle *h = hns3_get_handle(netdev);
	int ret;

	ret = h->ae_algo->ops->set_channels(h, new_tqp_num);
	if (ret)
		return ret;

	ret = hns3_get_ring_config(priv);
	if (ret)
		return ret;

	ret = hns3_nic_alloc_vector_data(priv);
	if (ret)
		goto err_alloc_vector;

	hns3_restore_coal(priv, tx, rx);

	ret = hns3_nic_init_vector_data(priv);
	if (ret)
		goto err_uninit_vector;

	ret = hns3_init_all_ring(priv);
	if (ret)
		goto err_put_ring;

	return 0;

err_put_ring:
	hns3_put_ring_config(priv);
err_uninit_vector:
	hns3_nic_uninit_vector_data(priv);
err_alloc_vector:
	hns3_nic_dealloc_vector_data(priv);
	return ret;
}