#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_5__ {struct hnae_queue* q; } ;
struct TYPE_4__ {struct hnae_queue* q; } ;
struct hnae_queue {TYPE_2__ tx_ring; TYPE_1__ rx_ring; } ;
struct ring_pair_cb {int used_by_vf; struct hnae_queue q; } ;
struct hnae_handle {int q_num; int vf_id; size_t dport_id; int /*<<< orphan*/  media_type; int /*<<< orphan*/  port_type; int /*<<< orphan*/  if_support; int /*<<< orphan*/  phy_dev; int /*<<< orphan*/  phy_if; struct hnae_queue** qs; int /*<<< orphan*/  coal_param; struct hnae_ae_dev* dev; int /*<<< orphan*/  owner_dev; } ;
struct hnae_vf_cb {size_t port_index; TYPE_3__* mac_cb; struct dsaf_device* dsaf_dev; struct hnae_handle ae_handle; } ;
struct hnae_ae_dev {int dummy; } ;
struct dsaf_device {TYPE_3__** mac_cb; int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  media_type; int /*<<< orphan*/  mac_type; int /*<<< orphan*/  if_support; int /*<<< orphan*/  phy_dev; int /*<<< orphan*/  phy_if; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct hnae_handle* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HNAE_LOWEST_LATENCY_COAL_PARAM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct ring_pair_cb* hns_ae_get_base_ring_pair (struct dsaf_device*,size_t) ; 
 struct dsaf_device* hns_ae_get_dsaf_dev (struct hnae_ae_dev*) ; 
 int hns_ae_get_q_num_per_vf (struct dsaf_device*,size_t) ; 
 int hns_ae_get_vf_num_per_port (struct dsaf_device*,size_t) ; 
 int /*<<< orphan*/  kfree (struct hnae_vf_cb*) ; 
 struct hnae_vf_cb* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct hnae_handle *hns_ae_get_handle(struct hnae_ae_dev *dev,
					     u32 port_id)
{
	int vfnum_per_port;
	int qnum_per_vf;
	int i;
	struct dsaf_device *dsaf_dev;
	struct hnae_handle *ae_handle;
	struct ring_pair_cb *ring_pair_cb;
	struct hnae_vf_cb *vf_cb;

	dsaf_dev = hns_ae_get_dsaf_dev(dev);

	ring_pair_cb = hns_ae_get_base_ring_pair(dsaf_dev, port_id);
	vfnum_per_port = hns_ae_get_vf_num_per_port(dsaf_dev, port_id);
	qnum_per_vf = hns_ae_get_q_num_per_vf(dsaf_dev, port_id);

	vf_cb = kzalloc(sizeof(*vf_cb) +
			qnum_per_vf * sizeof(struct hnae_queue *), GFP_KERNEL);
	if (unlikely(!vf_cb)) {
		dev_err(dsaf_dev->dev, "malloc vf_cb fail!\n");
		ae_handle = ERR_PTR(-ENOMEM);
		goto handle_err;
	}
	ae_handle = &vf_cb->ae_handle;
	/* ae_handle Init  */
	ae_handle->owner_dev = dsaf_dev->dev;
	ae_handle->dev = dev;
	ae_handle->q_num = qnum_per_vf;
	ae_handle->coal_param = HNAE_LOWEST_LATENCY_COAL_PARAM;

	/* find ring pair, and set vf id*/
	for (ae_handle->vf_id = 0;
		ae_handle->vf_id < vfnum_per_port; ae_handle->vf_id++) {
		if (!ring_pair_cb->used_by_vf)
			break;
		ring_pair_cb += qnum_per_vf;
	}
	if (ae_handle->vf_id >= vfnum_per_port) {
		dev_err(dsaf_dev->dev, "malloc queue fail!\n");
		ae_handle = ERR_PTR(-EINVAL);
		goto vf_id_err;
	}

	ae_handle->qs = (struct hnae_queue **)(&ae_handle->qs + 1);
	for (i = 0; i < qnum_per_vf; i++) {
		ae_handle->qs[i] = &ring_pair_cb->q;
		ae_handle->qs[i]->rx_ring.q = ae_handle->qs[i];
		ae_handle->qs[i]->tx_ring.q = ae_handle->qs[i];

		ring_pair_cb->used_by_vf = 1;
		ring_pair_cb++;
	}

	vf_cb->dsaf_dev = dsaf_dev;
	vf_cb->port_index = port_id;
	vf_cb->mac_cb = dsaf_dev->mac_cb[port_id];

	ae_handle->phy_if = vf_cb->mac_cb->phy_if;
	ae_handle->phy_dev = vf_cb->mac_cb->phy_dev;
	ae_handle->if_support = vf_cb->mac_cb->if_support;
	ae_handle->port_type = vf_cb->mac_cb->mac_type;
	ae_handle->media_type = vf_cb->mac_cb->media_type;
	ae_handle->dport_id = port_id;

	return ae_handle;
vf_id_err:
	kfree(vf_cb);
handle_err:
	return ae_handle;
}