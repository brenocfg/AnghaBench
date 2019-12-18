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
struct ipmmu_vmsa_domain {int /*<<< orphan*/  context_id; struct ipmmu_vmsa_device* mmu; } ;
struct ipmmu_vmsa_device {int /*<<< orphan*/ * utlb_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMUASID (unsigned int) ; 
 int /*<<< orphan*/  IMUCTR (unsigned int) ; 
 int IMUCTR_FLUSH ; 
 int IMUCTR_MMUEN ; 
 int IMUCTR_TTSEL_MMU (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipmmu_write (struct ipmmu_vmsa_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ipmmu_utlb_enable(struct ipmmu_vmsa_domain *domain,
			      unsigned int utlb)
{
	struct ipmmu_vmsa_device *mmu = domain->mmu;

	/*
	 * TODO: Reference-count the microTLB as several bus masters can be
	 * connected to the same microTLB.
	 */

	/* TODO: What should we set the ASID to ? */
	ipmmu_write(mmu, IMUASID(utlb), 0);
	/* TODO: Do we need to flush the microTLB ? */
	ipmmu_write(mmu, IMUCTR(utlb),
		    IMUCTR_TTSEL_MMU(domain->context_id) | IMUCTR_FLUSH |
		    IMUCTR_MMUEN);
	mmu->utlb_ctx[utlb] = domain->context_id;
}