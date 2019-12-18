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
struct siena_vf {scalar_t__ evq0_count; scalar_t__ peer_page_count; int /*<<< orphan*/ * peer_page_addrs; int /*<<< orphan*/  buf; } ;
struct siena_nic_data {struct siena_vf* vf; } ;
struct efx_nic {unsigned int vf_count; struct siena_nic_data* nic_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  efx_nic_free_buffer (struct efx_nic*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void efx_siena_sriov_vfs_fini(struct efx_nic *efx)
{
	struct siena_nic_data *nic_data = efx->nic_data;
	struct siena_vf *vf;
	unsigned int pos;

	for (pos = 0; pos < efx->vf_count; ++pos) {
		vf = nic_data->vf + pos;

		efx_nic_free_buffer(efx, &vf->buf);
		kfree(vf->peer_page_addrs);
		vf->peer_page_addrs = NULL;
		vf->peer_page_count = 0;

		vf->evq0_count = 0;
	}
}