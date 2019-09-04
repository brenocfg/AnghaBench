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
struct net_device {int dummy; } ;
struct enic {unsigned int rq_count; unsigned int wq_count; unsigned int intr_count; int /*<<< orphan*/ * rq; int /*<<< orphan*/ * intr; int /*<<< orphan*/ * napi; int /*<<< orphan*/  vdev; int /*<<< orphan*/ * wq; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ VNIC_DEV_INTR_MODE_MSIX ; 
 size_t enic_cq_wq (struct enic*,unsigned int) ; 
 int /*<<< orphan*/  enic_dev_add_station_addr (struct enic*) ; 
 int /*<<< orphan*/  enic_dev_enable (struct enic*) ; 
 int enic_dev_notify_set (struct enic*) ; 
 int /*<<< orphan*/  enic_dev_notify_unset (struct enic*) ; 
 int /*<<< orphan*/  enic_free_intr (struct enic*) ; 
 int /*<<< orphan*/  enic_free_rq_buf ; 
 int /*<<< orphan*/  enic_init_affinity_hint (struct enic*) ; 
 int /*<<< orphan*/  enic_is_dynamic (struct enic*) ; 
 int /*<<< orphan*/  enic_is_sriov_vf (struct enic*) ; 
 int /*<<< orphan*/  enic_notify_timer_start (struct enic*) ; 
 int enic_request_intr (struct enic*) ; 
 int /*<<< orphan*/  enic_rfs_timer_start (struct enic*) ; 
 int /*<<< orphan*/  enic_rq_alloc_buf ; 
 int /*<<< orphan*/  enic_set_affinity_hint (struct enic*) ; 
 int /*<<< orphan*/  enic_set_rx_mode (struct net_device*) ; 
 int /*<<< orphan*/  enic_unset_affinity_hint (struct enic*) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct enic* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_wake_all_queues (struct net_device*) ; 
 scalar_t__ vnic_dev_get_intr_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnic_intr_unmask (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnic_rq_clean (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ vnic_rq_desc_used (int /*<<< orphan*/ *) ; 
 int vnic_rq_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnic_rq_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnic_rq_fill (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnic_wq_enable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int enic_open(struct net_device *netdev)
{
	struct enic *enic = netdev_priv(netdev);
	unsigned int i;
	int err, ret;

	err = enic_request_intr(enic);
	if (err) {
		netdev_err(netdev, "Unable to request irq.\n");
		return err;
	}
	enic_init_affinity_hint(enic);
	enic_set_affinity_hint(enic);

	err = enic_dev_notify_set(enic);
	if (err) {
		netdev_err(netdev,
			"Failed to alloc notify buffer, aborting.\n");
		goto err_out_free_intr;
	}

	for (i = 0; i < enic->rq_count; i++) {
		/* enable rq before updating rq desc */
		vnic_rq_enable(&enic->rq[i]);
		vnic_rq_fill(&enic->rq[i], enic_rq_alloc_buf);
		/* Need at least one buffer on ring to get going */
		if (vnic_rq_desc_used(&enic->rq[i]) == 0) {
			netdev_err(netdev, "Unable to alloc receive buffers\n");
			err = -ENOMEM;
			goto err_out_free_rq;
		}
	}

	for (i = 0; i < enic->wq_count; i++)
		vnic_wq_enable(&enic->wq[i]);

	if (!enic_is_dynamic(enic) && !enic_is_sriov_vf(enic))
		enic_dev_add_station_addr(enic);

	enic_set_rx_mode(netdev);

	netif_tx_wake_all_queues(netdev);

	for (i = 0; i < enic->rq_count; i++)
		napi_enable(&enic->napi[i]);

	if (vnic_dev_get_intr_mode(enic->vdev) == VNIC_DEV_INTR_MODE_MSIX)
		for (i = 0; i < enic->wq_count; i++)
			napi_enable(&enic->napi[enic_cq_wq(enic, i)]);
	enic_dev_enable(enic);

	for (i = 0; i < enic->intr_count; i++)
		vnic_intr_unmask(&enic->intr[i]);

	enic_notify_timer_start(enic);
	enic_rfs_timer_start(enic);

	return 0;

err_out_free_rq:
	for (i = 0; i < enic->rq_count; i++) {
		ret = vnic_rq_disable(&enic->rq[i]);
		if (!ret)
			vnic_rq_clean(&enic->rq[i], enic_free_rq_buf);
	}
	enic_dev_notify_unset(enic);
err_out_free_intr:
	enic_unset_affinity_hint(enic);
	enic_free_intr(enic);

	return err;
}