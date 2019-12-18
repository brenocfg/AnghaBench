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
struct ipmmu_vmsa_domain {struct ipmmu_vmsa_device* mmu; } ;
struct ipmmu_vmsa_device {int /*<<< orphan*/ * utlb_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMUCTR (unsigned int) ; 
 int /*<<< orphan*/  IPMMU_CTX_INVALID ; 
 int /*<<< orphan*/  ipmmu_write (struct ipmmu_vmsa_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipmmu_utlb_disable(struct ipmmu_vmsa_domain *domain,
			       unsigned int utlb)
{
	struct ipmmu_vmsa_device *mmu = domain->mmu;

	ipmmu_write(mmu, IMUCTR(utlb), 0);
	mmu->utlb_ctx[utlb] = IPMMU_CTX_INVALID;
}