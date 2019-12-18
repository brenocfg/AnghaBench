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
struct siena_vf {int /*<<< orphan*/  reset_work; int /*<<< orphan*/  index; } ;
struct efx_nic {int /*<<< orphan*/  net_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  hw ; 
 scalar_t__ map_vi_index (struct efx_nic*,unsigned int,struct siena_vf**,unsigned int*) ; 
 scalar_t__ net_ratelimit () ; 
 int /*<<< orphan*/  netif_err (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfdi_workqueue ; 

void efx_siena_sriov_desc_fetch_err(struct efx_nic *efx, unsigned dmaq)
{
	struct siena_vf *vf;
	unsigned int rel;

	if (map_vi_index(efx, dmaq, &vf, &rel))
		return;

	if (net_ratelimit())
		netif_err(efx, hw, efx->net_dev,
			  "VF %d DMA Q %d reports descriptor fetch error.\n",
			  vf->index, rel);
	queue_work(vfdi_workqueue, &vf->reset_work);
}