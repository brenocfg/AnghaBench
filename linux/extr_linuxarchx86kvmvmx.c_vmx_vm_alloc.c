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
struct kvm {int dummy; } ;
struct kvm_vmx {struct kvm kvm; } ;

/* Variables and functions */
 struct kvm_vmx* vzalloc (int) ; 

__attribute__((used)) static struct kvm *vmx_vm_alloc(void)
{
	struct kvm_vmx *kvm_vmx = vzalloc(sizeof(struct kvm_vmx));
	return &kvm_vmx->kvm;
}