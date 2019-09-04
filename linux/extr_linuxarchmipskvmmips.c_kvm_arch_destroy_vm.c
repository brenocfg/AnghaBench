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
 int /*<<< orphan*/  kvm_mips_free_gpa_pt (struct kvm*) ; 
 int /*<<< orphan*/  kvm_mips_free_vcpus (struct kvm*) ; 

void kvm_arch_destroy_vm(struct kvm *kvm)
{
	kvm_mips_free_vcpus(kvm);
	kvm_mips_free_gpa_pt(kvm);
}