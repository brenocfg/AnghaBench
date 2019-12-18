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
struct enic {unsigned int rq_count; unsigned int wq_count; int /*<<< orphan*/ * napi; int /*<<< orphan*/  vdev; } ;

/* Variables and functions */
 scalar_t__ VNIC_DEV_INTR_MODE_MSIX ; 
 int /*<<< orphan*/  enic_clear_intr_mode (struct enic*) ; 
 size_t enic_cq_wq (struct enic*,unsigned int) ; 
 int /*<<< orphan*/  enic_free_affinity_hint (struct enic*) ; 
 int /*<<< orphan*/  enic_free_vnic_resources (struct enic*) ; 
 int /*<<< orphan*/  napi_hash_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 
 scalar_t__ vnic_dev_get_intr_mode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void enic_dev_deinit(struct enic *enic)
{
	unsigned int i;

	for (i = 0; i < enic->rq_count; i++) {
		napi_hash_del(&enic->napi[i]);
		netif_napi_del(&enic->napi[i]);
	}
	if (vnic_dev_get_intr_mode(enic->vdev) == VNIC_DEV_INTR_MODE_MSIX)
		for (i = 0; i < enic->wq_count; i++)
			netif_napi_del(&enic->napi[enic_cq_wq(enic, i)]);

	enic_free_vnic_resources(enic);
	enic_clear_intr_mode(enic);
	enic_free_affinity_hint(enic);
}