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
struct TYPE_2__ {int /*<<< orphan*/  enabled_hcalls; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __set_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int* default_hcall_list ; 
 int /*<<< orphan*/  kvmppc_hcall_impl_pr (unsigned int) ; 

void kvmppc_pr_init_default_hcalls(struct kvm *kvm)
{
	int i;
	unsigned int hcall;

	for (i = 0; default_hcall_list[i]; ++i) {
		hcall = default_hcall_list[i];
		WARN_ON(!kvmppc_hcall_impl_pr(hcall));
		__set_bit(hcall / 4, kvm->arch.enabled_hcalls);
	}
}