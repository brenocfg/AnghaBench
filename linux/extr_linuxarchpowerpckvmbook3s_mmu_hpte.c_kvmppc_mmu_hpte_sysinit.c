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
struct hpte_cache {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hpte_cache ; 
 int /*<<< orphan*/  kmem_cache_create (char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int kvmppc_mmu_hpte_sysinit(void)
{
	/* init hpte slab cache */
	hpte_cache = kmem_cache_create("kvm-spt", sizeof(struct hpte_cache),
				       sizeof(struct hpte_cache), 0, NULL);

	return 0;
}