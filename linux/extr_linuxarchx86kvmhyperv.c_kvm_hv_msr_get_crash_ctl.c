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
typedef  int /*<<< orphan*/  u64 ;
struct kvm_vcpu {TYPE_2__* kvm; } ;
struct kvm_hv {int /*<<< orphan*/  hv_crash_ctl; } ;
struct TYPE_3__ {struct kvm_hv hyperv; } ;
struct TYPE_4__ {TYPE_1__ arch; } ;

/* Variables and functions */

__attribute__((used)) static int kvm_hv_msr_get_crash_ctl(struct kvm_vcpu *vcpu, u64 *pdata)
{
	struct kvm_hv *hv = &vcpu->kvm->arch.hyperv;

	*pdata = hv->hv_crash_ctl;
	return 0;
}