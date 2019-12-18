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
typedef  int /*<<< orphan*/  u32 ;
struct ipmmu_vmsa_domain {unsigned int context_id; TYPE_1__* mmu; } ;
struct TYPE_2__ {int /*<<< orphan*/  root; } ;

/* Variables and functions */
 unsigned int IM_CTX_SIZE ; 
 int /*<<< orphan*/  ipmmu_read (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static u32 ipmmu_ctx_read_root(struct ipmmu_vmsa_domain *domain,
			       unsigned int reg)
{
	return ipmmu_read(domain->mmu->root,
			  domain->context_id * IM_CTX_SIZE + reg);
}