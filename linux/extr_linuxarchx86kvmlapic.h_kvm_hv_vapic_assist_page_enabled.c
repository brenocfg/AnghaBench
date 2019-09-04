#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int hv_vapic; } ;
struct TYPE_4__ {TYPE_1__ hyperv; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;

/* Variables and functions */
 int HV_X64_MSR_VP_ASSIST_PAGE_ENABLE ; 

__attribute__((used)) static inline bool kvm_hv_vapic_assist_page_enabled(struct kvm_vcpu *vcpu)
{
	return vcpu->arch.hyperv.hv_vapic & HV_X64_MSR_VP_ASSIST_PAGE_ENABLE;
}