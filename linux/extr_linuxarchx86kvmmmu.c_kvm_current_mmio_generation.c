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
struct kvm_vcpu {int dummy; } ;
struct TYPE_2__ {unsigned int generation; } ;

/* Variables and functions */
 unsigned int MMIO_GEN_MASK ; 
 TYPE_1__* kvm_vcpu_memslots (struct kvm_vcpu*) ; 

__attribute__((used)) static unsigned int kvm_current_mmio_generation(struct kvm_vcpu *vcpu)
{
	return kvm_vcpu_memslots(vcpu)->generation & MMIO_GEN_MASK;
}