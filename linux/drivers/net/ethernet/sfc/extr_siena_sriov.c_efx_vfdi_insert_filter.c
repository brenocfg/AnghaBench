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
struct TYPE_5__ {unsigned int rxq; int flags; } ;
struct TYPE_6__ {TYPE_2__ mac_filter; } ;
struct vfdi_req {TYPE_3__ u; } ;
struct TYPE_4__ {struct vfdi_req* addr; } ;
struct siena_vf {int rx_filtering; unsigned int rx_filter_flags; unsigned int rx_filter_qid; int /*<<< orphan*/  pci_name; TYPE_1__ buf; struct efx_nic* efx; } ;
struct siena_nic_data {int /*<<< orphan*/  peer_work; } ;
struct efx_nic {int /*<<< orphan*/  net_dev; struct siena_nic_data* nic_data; } ;

/* Variables and functions */
 unsigned int EFX_FILTER_FLAG_RX_RSS ; 
 unsigned int EFX_FILTER_FLAG_RX_SCATTER ; 
 int VFDI_MAC_FILTER_FLAG_RSS ; 
 int VFDI_MAC_FILTER_FLAG_SCATTER ; 
 int VFDI_RC_EINVAL ; 
 int VFDI_RC_SUCCESS ; 
 scalar_t__ bad_vf_index (struct efx_nic*,unsigned int) ; 
 int /*<<< orphan*/  efx_siena_sriov_reset_rx_filter (struct siena_vf*) ; 
 int /*<<< orphan*/  hw ; 
 scalar_t__ net_ratelimit () ; 
 int /*<<< orphan*/  netif_err (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfdi_workqueue ; 

__attribute__((used)) static int efx_vfdi_insert_filter(struct siena_vf *vf)
{
	struct efx_nic *efx = vf->efx;
	struct siena_nic_data *nic_data = efx->nic_data;
	struct vfdi_req *req = vf->buf.addr;
	unsigned vf_rxq = req->u.mac_filter.rxq;
	unsigned flags;

	if (bad_vf_index(efx, vf_rxq) || vf->rx_filtering) {
		if (net_ratelimit())
			netif_err(efx, hw, efx->net_dev,
				  "ERROR: Invalid INSERT_FILTER from %s: rxq %d "
				  "flags 0x%x\n", vf->pci_name, vf_rxq,
				  req->u.mac_filter.flags);
		return VFDI_RC_EINVAL;
	}

	flags = 0;
	if (req->u.mac_filter.flags & VFDI_MAC_FILTER_FLAG_RSS)
		flags |= EFX_FILTER_FLAG_RX_RSS;
	if (req->u.mac_filter.flags & VFDI_MAC_FILTER_FLAG_SCATTER)
		flags |= EFX_FILTER_FLAG_RX_SCATTER;
	vf->rx_filter_flags = flags;
	vf->rx_filter_qid = vf_rxq;
	vf->rx_filtering = true;

	efx_siena_sriov_reset_rx_filter(vf);
	queue_work(vfdi_workqueue, &nic_data->peer_work);

	return VFDI_RC_SUCCESS;
}