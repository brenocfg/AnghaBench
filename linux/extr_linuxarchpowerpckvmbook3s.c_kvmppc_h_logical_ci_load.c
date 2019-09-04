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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct kvm_vcpu {TYPE_1__* kvm; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  __be64 ;
typedef  int /*<<< orphan*/  __be32 ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_2__ {int /*<<< orphan*/  srcu; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int H_SUCCESS ; 
 int H_TOO_HARD ; 
 int /*<<< orphan*/  KVM_MMIO_BUS ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_power_of_2 (unsigned long) ; 
 int kvm_io_bus_read (struct kvm_vcpu*,int /*<<< orphan*/ ,unsigned long,unsigned long,int /*<<< orphan*/ *) ; 
 unsigned long kvmppc_get_gpr (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  kvmppc_set_gpr (struct kvm_vcpu*,int,int /*<<< orphan*/ ) ; 
 int srcu_read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srcu_read_unlock (int /*<<< orphan*/ *,int) ; 

int kvmppc_h_logical_ci_load(struct kvm_vcpu *vcpu)
{
	unsigned long size = kvmppc_get_gpr(vcpu, 4);
	unsigned long addr = kvmppc_get_gpr(vcpu, 5);
	u64 buf;
	int srcu_idx;
	int ret;

	if (!is_power_of_2(size) || (size > sizeof(buf)))
		return H_TOO_HARD;

	srcu_idx = srcu_read_lock(&vcpu->kvm->srcu);
	ret = kvm_io_bus_read(vcpu, KVM_MMIO_BUS, addr, size, &buf);
	srcu_read_unlock(&vcpu->kvm->srcu, srcu_idx);
	if (ret != 0)
		return H_TOO_HARD;

	switch (size) {
	case 1:
		kvmppc_set_gpr(vcpu, 4, *(u8 *)&buf);
		break;

	case 2:
		kvmppc_set_gpr(vcpu, 4, be16_to_cpu(*(__be16 *)&buf));
		break;

	case 4:
		kvmppc_set_gpr(vcpu, 4, be32_to_cpu(*(__be32 *)&buf));
		break;

	case 8:
		kvmppc_set_gpr(vcpu, 4, be64_to_cpu(*(__be64 *)&buf));
		break;

	default:
		BUG();
	}

	return H_SUCCESS;
}