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
typedef  int ulong ;
struct kvmppc_pte {int raddr; int eaddr; int /*<<< orphan*/  may_execute; int /*<<< orphan*/  may_read; } ;
struct TYPE_4__ {int magic_page_pa; void* shared; } ;
struct TYPE_3__ {int /*<<< orphan*/  ld; } ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; TYPE_2__ arch; TYPE_1__ stat; } ;

/* Variables and functions */
 int EMULATE_DONE ; 
 int EMULATE_DO_MMIO ; 
 int ENOEXEC ; 
 int EPERM ; 
 int KVM_PAM ; 
 int MSR_PR ; 
 int PAGE_MASK ; 
 int /*<<< orphan*/  XLATE_DATA ; 
 int /*<<< orphan*/  XLATE_INST ; 
 int /*<<< orphan*/  XLATE_READ ; 
 scalar_t__ kvm_read_guest (int /*<<< orphan*/ ,int,void*,int) ; 
 int kvmppc_get_msr (struct kvm_vcpu*) ; 
 scalar_t__ kvmppc_supports_magic_page (struct kvm_vcpu*) ; 
 int kvmppc_xlate (struct kvm_vcpu*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct kvmppc_pte*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 

int kvmppc_ld(struct kvm_vcpu *vcpu, ulong *eaddr, int size, void *ptr,
		      bool data)
{
	ulong mp_pa = vcpu->arch.magic_page_pa & KVM_PAM & PAGE_MASK;
	struct kvmppc_pte pte;
	int rc;

	vcpu->stat.ld++;

	rc = kvmppc_xlate(vcpu, *eaddr, data ? XLATE_DATA : XLATE_INST,
			  XLATE_READ, &pte);
	if (rc)
		return rc;

	*eaddr = pte.raddr;

	if (!pte.may_read)
		return -EPERM;

	if (!data && !pte.may_execute)
		return -ENOEXEC;

	/* Magic page override */
	if (kvmppc_supports_magic_page(vcpu) && mp_pa &&
	    ((pte.raddr & KVM_PAM & PAGE_MASK) == mp_pa) &&
	    !(kvmppc_get_msr(vcpu) & MSR_PR)) {
		void *magic = vcpu->arch.shared;
		magic += pte.eaddr & 0xfff;
		memcpy(ptr, magic, size);
		return EMULATE_DONE;
	}

	if (kvm_read_guest(vcpu->kvm, pte.raddr, ptr, size))
		return EMULATE_DO_MMIO;

	return EMULATE_DONE;
}