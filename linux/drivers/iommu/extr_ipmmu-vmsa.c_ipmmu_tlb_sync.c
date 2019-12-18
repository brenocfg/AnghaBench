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
struct ipmmu_vmsa_domain {TYPE_1__* mmu; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMCTR ; 
 int IMCTR_FLUSH ; 
 unsigned int TLB_LOOP_TIMEOUT ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dev_err_ratelimited (int /*<<< orphan*/ ,char*) ; 
 int ipmmu_ctx_read_root (struct ipmmu_vmsa_domain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void ipmmu_tlb_sync(struct ipmmu_vmsa_domain *domain)
{
	unsigned int count = 0;

	while (ipmmu_ctx_read_root(domain, IMCTR) & IMCTR_FLUSH) {
		cpu_relax();
		if (++count == TLB_LOOP_TIMEOUT) {
			dev_err_ratelimited(domain->mmu->dev,
			"TLB sync timed out -- MMU may be deadlocked\n");
			return;
		}
		udelay(1);
	}
}