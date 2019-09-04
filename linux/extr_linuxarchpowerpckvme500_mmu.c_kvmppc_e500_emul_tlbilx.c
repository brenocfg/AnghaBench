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
struct kvmppc_vcpu_e500 {int dummy; } ;
struct kvm_vcpu {int dummy; } ;
typedef  int /*<<< orphan*/  gva_t ;

/* Variables and functions */
 int EMULATE_DONE ; 
 int get_cur_spid (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  tlbilx_all (struct kvmppc_vcpu_e500*,int,int,int) ; 
 int /*<<< orphan*/  tlbilx_one (struct kvmppc_vcpu_e500*,int,int /*<<< orphan*/ ) ; 
 struct kvmppc_vcpu_e500* to_e500 (struct kvm_vcpu*) ; 

int kvmppc_e500_emul_tlbilx(struct kvm_vcpu *vcpu, int type, gva_t ea)
{
	struct kvmppc_vcpu_e500 *vcpu_e500 = to_e500(vcpu);
	int pid = get_cur_spid(vcpu);

	if (type == 0 || type == 1) {
		tlbilx_all(vcpu_e500, 0, pid, type);
		tlbilx_all(vcpu_e500, 1, pid, type);
	} else if (type == 3) {
		tlbilx_one(vcpu_e500, pid, ea);
	}

	return EMULATE_DONE;
}