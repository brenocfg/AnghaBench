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
struct siena_vf {unsigned int index; int rx_filter_id; int tx_filter_id; int /*<<< orphan*/  txq_lock; int /*<<< orphan*/  status_lock; int /*<<< orphan*/  flush_waitq; int /*<<< orphan*/  reset_work; int /*<<< orphan*/  req; int /*<<< orphan*/  tx_filter_mode; struct efx_nic* efx; } ;
struct siena_nic_data {struct siena_vf* vf; } ;
struct efx_nic {unsigned int vf_count; struct siena_nic_data* nic_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VF_TX_FILTER_AUTO ; 
 int /*<<< orphan*/  efx_siena_sriov_reset_vf_work ; 
 int /*<<< orphan*/  efx_siena_sriov_vfdi ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct siena_vf* kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int efx_siena_sriov_vf_alloc(struct efx_nic *efx)
{
	unsigned index;
	struct siena_vf *vf;
	struct siena_nic_data *nic_data = efx->nic_data;

	nic_data->vf = kcalloc(efx->vf_count, sizeof(*nic_data->vf),
			       GFP_KERNEL);
	if (!nic_data->vf)
		return -ENOMEM;

	for (index = 0; index < efx->vf_count; ++index) {
		vf = nic_data->vf + index;

		vf->efx = efx;
		vf->index = index;
		vf->rx_filter_id = -1;
		vf->tx_filter_mode = VF_TX_FILTER_AUTO;
		vf->tx_filter_id = -1;
		INIT_WORK(&vf->req, efx_siena_sriov_vfdi);
		INIT_WORK(&vf->reset_work, efx_siena_sriov_reset_vf_work);
		init_waitqueue_head(&vf->flush_waitq);
		mutex_init(&vf->status_lock);
		mutex_init(&vf->txq_lock);
	}

	return 0;
}