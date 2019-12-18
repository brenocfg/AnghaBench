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
typedef  scalar_t__ u64 ;
struct qbman_pull_desc {int verb; int /*<<< orphan*/  rsp_addr; scalar_t__ rsp_addr_virt; } ;
struct dpaa2_dq {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int QB_VDQCR_VERB_RLS_SHIFT ; 
 int QB_VDQCR_VERB_WAE_SHIFT ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 

void qbman_pull_desc_set_storage(struct qbman_pull_desc *d,
				 struct dpaa2_dq *storage,
				 dma_addr_t storage_phys,
				 int stash)
{
	/* save the virtual address */
	d->rsp_addr_virt = (u64)(uintptr_t)storage;

	if (!storage) {
		d->verb &= ~(1 << QB_VDQCR_VERB_RLS_SHIFT);
		return;
	}
	d->verb |= 1 << QB_VDQCR_VERB_RLS_SHIFT;
	if (stash)
		d->verb |= 1 << QB_VDQCR_VERB_WAE_SHIFT;
	else
		d->verb &= ~(1 << QB_VDQCR_VERB_WAE_SHIFT);

	d->rsp_addr = cpu_to_le64(storage_phys);
}