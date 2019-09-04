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
struct enic {unsigned int intr_count; unsigned int rq_count; unsigned int wq_count; unsigned int cq_count; int /*<<< orphan*/ * intr; int /*<<< orphan*/ * cq; int /*<<< orphan*/ * rq; int /*<<< orphan*/ * wq; int /*<<< orphan*/ * napi; int /*<<< orphan*/  vdev; int /*<<< orphan*/  notify_timer; } ;

/* Variables and functions */
 scalar_t__ VNIC_DEV_INTR_MODE_MSIX ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 size_t enic_cq_wq (struct enic*,unsigned int) ; 
 int /*<<< orphan*/  enic_dev_del_station_addr (struct enic*) ; 
 int /*<<< orphan*/  enic_dev_disable (struct enic*) ; 
 int /*<<< orphan*/  enic_dev_notify_unset (struct enic*) ; 
 int /*<<< orphan*/  enic_free_intr (struct enic*) ; 
 int /*<<< orphan*/  enic_free_rq_buf ; 
 int /*<<< orphan*/  enic_free_wq_buf ; 
 int /*<<< orphan*/  enic_is_dynamic (struct enic*) ; 
 int /*<<< orphan*/  enic_is_sriov_vf (struct enic*) ; 
 int /*<<< orphan*/  enic_rfs_flw_tbl_free (struct enic*) ; 
 int /*<<< orphan*/  enic_synchronize_irqs (struct enic*) ; 
 int /*<<< orphan*/  enic_unset_affinity_hint (struct enic*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct enic* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_disable (struct net_device*) ; 
 int /*<<< orphan*/  vnic_cq_clean (int /*<<< orphan*/ *) ; 
 scalar_t__ vnic_dev_get_intr_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnic_intr_clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnic_intr_mask (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnic_intr_masked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnic_rq_clean (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int vnic_rq_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnic_wq_clean (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int vnic_wq_disable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int enic_stop(struct net_device *netdev)
{
	struct enic *enic = netdev_priv(netdev);
	unsigned int i;
	int err;

	for (i = 0; i < enic->intr_count; i++) {
		vnic_intr_mask(&enic->intr[i]);
		(void)vnic_intr_masked(&enic->intr[i]); /* flush write */
	}

	enic_synchronize_irqs(enic);

	del_timer_sync(&enic->notify_timer);
	enic_rfs_flw_tbl_free(enic);

	enic_dev_disable(enic);

	for (i = 0; i < enic->rq_count; i++)
		napi_disable(&enic->napi[i]);

	netif_carrier_off(netdev);
	netif_tx_disable(netdev);
	if (vnic_dev_get_intr_mode(enic->vdev) == VNIC_DEV_INTR_MODE_MSIX)
		for (i = 0; i < enic->wq_count; i++)
			napi_disable(&enic->napi[enic_cq_wq(enic, i)]);

	if (!enic_is_dynamic(enic) && !enic_is_sriov_vf(enic))
		enic_dev_del_station_addr(enic);

	for (i = 0; i < enic->wq_count; i++) {
		err = vnic_wq_disable(&enic->wq[i]);
		if (err)
			return err;
	}
	for (i = 0; i < enic->rq_count; i++) {
		err = vnic_rq_disable(&enic->rq[i]);
		if (err)
			return err;
	}

	enic_dev_notify_unset(enic);
	enic_unset_affinity_hint(enic);
	enic_free_intr(enic);

	for (i = 0; i < enic->wq_count; i++)
		vnic_wq_clean(&enic->wq[i], enic_free_wq_buf);
	for (i = 0; i < enic->rq_count; i++)
		vnic_rq_clean(&enic->rq[i], enic_free_rq_buf);
	for (i = 0; i < enic->cq_count; i++)
		vnic_cq_clean(&enic->cq[i]);
	for (i = 0; i < enic->intr_count; i++)
		vnic_intr_clean(&enic->intr[i]);

	return 0;
}