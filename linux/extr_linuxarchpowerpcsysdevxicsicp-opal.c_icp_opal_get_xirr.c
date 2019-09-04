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
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 unsigned int be32_to_cpu (int /*<<< orphan*/ ) ; 
 unsigned int kvmppc_get_xics_latch () ; 
 scalar_t__ opal_int_get_xirr (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static unsigned int icp_opal_get_xirr(void)
{
	unsigned int kvm_xirr;
	__be32 hw_xirr;
	int64_t rc;

	/* Handle an interrupt latched by KVM first */
	kvm_xirr = kvmppc_get_xics_latch();
	if (kvm_xirr)
		return kvm_xirr;

	/* Then ask OPAL */
	rc = opal_int_get_xirr(&hw_xirr, false);
	if (rc < 0)
		return 0;
	return be32_to_cpu(hw_xirr);
}