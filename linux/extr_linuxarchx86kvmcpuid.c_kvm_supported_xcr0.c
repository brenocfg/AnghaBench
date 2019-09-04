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
typedef  int u64 ;

/* Variables and functions */
 int KVM_SUPPORTED_XCR0 ; 
 int XFEATURE_MASK_BNDCSR ; 
 int XFEATURE_MASK_BNDREGS ; 
 int host_xcr0 ; 
 int /*<<< orphan*/  kvm_mpx_supported () ; 

u64 kvm_supported_xcr0(void)
{
	u64 xcr0 = KVM_SUPPORTED_XCR0 & host_xcr0;

	if (!kvm_mpx_supported())
		xcr0 &= ~(XFEATURE_MASK_BNDREGS | XFEATURE_MASK_BNDCSR);

	return xcr0;
}