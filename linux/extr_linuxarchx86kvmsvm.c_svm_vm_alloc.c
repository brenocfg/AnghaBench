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
struct kvm_svm {struct kvm kvm; } ;

/* Variables and functions */
 struct kvm_svm* vzalloc (int) ; 

__attribute__((used)) static struct kvm *svm_vm_alloc(void)
{
	struct kvm_svm *kvm_svm = vzalloc(sizeof(struct kvm_svm));
	return &kvm_svm->kvm;
}