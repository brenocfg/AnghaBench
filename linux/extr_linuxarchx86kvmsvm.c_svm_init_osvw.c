#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int length; unsigned long long status; } ;
struct TYPE_5__ {TYPE_1__ osvw; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct TYPE_6__ {int x86; } ;

/* Variables and functions */
 TYPE_3__ boot_cpu_data ; 
 int osvw_len ; 
 unsigned long long osvw_status ; 

__attribute__((used)) static void svm_init_osvw(struct kvm_vcpu *vcpu)
{
	/*
	 * Guests should see errata 400 and 415 as fixed (assuming that
	 * HLT and IO instructions are intercepted).
	 */
	vcpu->arch.osvw.length = (osvw_len >= 3) ? (osvw_len) : 3;
	vcpu->arch.osvw.status = osvw_status & ~(6ULL);

	/*
	 * By increasing VCPU's osvw.length to 3 we are telling the guest that
	 * all osvw.status bits inside that length, including bit 0 (which is
	 * reserved for erratum 298), are valid. However, if host processor's
	 * osvw_len is 0 then osvw_status[0] carries no information. We need to
	 * be conservative here and therefore we tell the guest that erratum 298
	 * is present (because we really don't know).
	 */
	if (osvw_len == 0 && boot_cpu_data.x86 == 0x10)
		vcpu->arch.osvw.status |= 1;
}