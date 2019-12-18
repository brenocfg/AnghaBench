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
struct ipmmu_vmsa_domain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipmmu_tlb_invalidate (struct ipmmu_vmsa_domain*) ; 

__attribute__((used)) static void ipmmu_tlb_flush_all(void *cookie)
{
	struct ipmmu_vmsa_domain *domain = cookie;

	ipmmu_tlb_invalidate(domain);
}