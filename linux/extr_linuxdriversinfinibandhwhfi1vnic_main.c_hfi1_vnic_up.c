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
struct net_device {int dummy; } ;
struct hfi1_vnic_vport_info {int num_rx_q; int /*<<< orphan*/  flags; struct hfi1_vnic_rx_queue* rxq; scalar_t__ vesw_id; struct net_device* netdev; struct hfi1_devdata* dd; } ;
struct hfi1_vnic_rx_queue {int /*<<< orphan*/  napi; int /*<<< orphan*/  skbq; } ;
struct TYPE_2__ {int /*<<< orphan*/  vesw_idr; } ;
struct hfi1_devdata {TYPE_1__ vnic; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int /*<<< orphan*/  HFI1_VNIC_UP ; 
 int idr_alloc (int /*<<< orphan*/ *,struct hfi1_vnic_vport_info*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_start_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hfi1_vnic_up(struct hfi1_vnic_vport_info *vinfo)
{
	struct hfi1_devdata *dd = vinfo->dd;
	struct net_device *netdev = vinfo->netdev;
	int i, rc;

	/* ensure virtual eth switch id is valid */
	if (!vinfo->vesw_id)
		return -EINVAL;

	rc = idr_alloc(&dd->vnic.vesw_idr, vinfo, vinfo->vesw_id,
		       vinfo->vesw_id + 1, GFP_NOWAIT);
	if (rc < 0)
		return rc;

	for (i = 0; i < vinfo->num_rx_q; i++) {
		struct hfi1_vnic_rx_queue *rxq = &vinfo->rxq[i];

		skb_queue_head_init(&rxq->skbq);
		napi_enable(&rxq->napi);
	}

	netif_carrier_on(netdev);
	netif_tx_start_all_queues(netdev);
	set_bit(HFI1_VNIC_UP, &vinfo->flags);

	return 0;
}