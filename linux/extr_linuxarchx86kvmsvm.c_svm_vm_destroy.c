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

/* Variables and functions */
 int /*<<< orphan*/  avic_vm_destroy (struct kvm*) ; 
 int /*<<< orphan*/  sev_vm_destroy (struct kvm*) ; 

__attribute__((used)) static void svm_vm_destroy(struct kvm *kvm)
{
	avic_vm_destroy(kvm);
	sev_vm_destroy(kvm);
}