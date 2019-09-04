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
typedef  void* u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct kvm_vcpu {TYPE_2__* run; } ;
struct TYPE_3__ {int /*<<< orphan*/  sel2; void* sel1; void* fc; void* ar; int /*<<< orphan*/  addr; } ;
struct TYPE_4__ {TYPE_1__ s390_stsi; int /*<<< orphan*/  exit_reason; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_EXIT_S390_STSI ; 

__attribute__((used)) static void insert_stsi_usr_data(struct kvm_vcpu *vcpu, u64 addr, u8 ar,
				 u8 fc, u8 sel1, u16 sel2)
{
	vcpu->run->exit_reason = KVM_EXIT_S390_STSI;
	vcpu->run->s390_stsi.addr = addr;
	vcpu->run->s390_stsi.ar = ar;
	vcpu->run->s390_stsi.fc = fc;
	vcpu->run->s390_stsi.sel1 = sel1;
	vcpu->run->s390_stsi.sel2 = sel2;
}