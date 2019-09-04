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
struct kvm_pmc {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ KVM_PMC_FIXED ; 

__attribute__((used)) static inline bool pmc_is_fixed(struct kvm_pmc *pmc)
{
	return pmc->type == KVM_PMC_FIXED;
}