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
union vnic_rss_cpu {TYPE_1__* cpu; } ;
typedef  int u8 ;
struct enic {unsigned int rq_count; int /*<<< orphan*/  pdev; int /*<<< orphan*/  devcmd_lock; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {unsigned int* b; } ;

/* Variables and functions */
 int ENOMEM ; 
 int enic_set_rss_cpu (struct enic*,int /*<<< orphan*/ ,int) ; 
 union vnic_rss_cpu* pci_alloc_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,union vnic_rss_cpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int enic_set_rsscpu(struct enic *enic, u8 rss_hash_bits)
{
	dma_addr_t rss_cpu_buf_pa;
	union vnic_rss_cpu *rss_cpu_buf_va = NULL;
	unsigned int i;
	int err;

	rss_cpu_buf_va = pci_alloc_consistent(enic->pdev,
		sizeof(union vnic_rss_cpu), &rss_cpu_buf_pa);
	if (!rss_cpu_buf_va)
		return -ENOMEM;

	for (i = 0; i < (1 << rss_hash_bits); i++)
		(*rss_cpu_buf_va).cpu[i/4].b[i%4] = i % enic->rq_count;

	spin_lock_bh(&enic->devcmd_lock);
	err = enic_set_rss_cpu(enic,
		rss_cpu_buf_pa,
		sizeof(union vnic_rss_cpu));
	spin_unlock_bh(&enic->devcmd_lock);

	pci_free_consistent(enic->pdev, sizeof(union vnic_rss_cpu),
		rss_cpu_buf_va, rss_cpu_buf_pa);

	return err;
}