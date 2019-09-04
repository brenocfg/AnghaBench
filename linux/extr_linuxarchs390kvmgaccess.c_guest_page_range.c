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
typedef  union asce {int dummy; } asce ;
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_5__ {TYPE_1__* sie_block; } ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; TYPE_2__ arch; } ;
typedef  int /*<<< orphan*/  psw_t ;
typedef  enum prot_type { ____Placeholder_prot_type } prot_type ;
typedef  enum gacc_mode { ____Placeholder_gacc_mode } gacc_mode ;
struct TYPE_6__ {scalar_t__ dat; } ;
struct TYPE_4__ {int /*<<< orphan*/  gpsw; } ;

/* Variables and functions */
 int GACC_STORE ; 
 unsigned long PAGE_MASK ; 
 scalar_t__ PAGE_SIZE ; 
 int PGM_ADDRESSING ; 
 int PGM_PROTECTION ; 
 int PROT_TYPE_LA ; 
 int guest_translate (struct kvm_vcpu*,unsigned long,unsigned long*,union asce const,int,int*) ; 
 scalar_t__ is_low_address (unsigned long) ; 
 scalar_t__ kvm_is_error_gpa (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long kvm_s390_logical_to_effective (struct kvm_vcpu*,unsigned long) ; 
 unsigned long kvm_s390_real_to_abs (struct kvm_vcpu*,unsigned long) ; 
 int low_address_protection_enabled (struct kvm_vcpu*,union asce const) ; 
 TYPE_3__ psw_bits (int /*<<< orphan*/ ) ; 
 int trans_exc (struct kvm_vcpu*,int,unsigned long,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int guest_page_range(struct kvm_vcpu *vcpu, unsigned long ga, u8 ar,
			    unsigned long *pages, unsigned long nr_pages,
			    const union asce asce, enum gacc_mode mode)
{
	psw_t *psw = &vcpu->arch.sie_block->gpsw;
	int lap_enabled, rc = 0;
	enum prot_type prot;

	lap_enabled = low_address_protection_enabled(vcpu, asce);
	while (nr_pages) {
		ga = kvm_s390_logical_to_effective(vcpu, ga);
		if (mode == GACC_STORE && lap_enabled && is_low_address(ga))
			return trans_exc(vcpu, PGM_PROTECTION, ga, ar, mode,
					 PROT_TYPE_LA);
		ga &= PAGE_MASK;
		if (psw_bits(*psw).dat) {
			rc = guest_translate(vcpu, ga, pages, asce, mode, &prot);
			if (rc < 0)
				return rc;
		} else {
			*pages = kvm_s390_real_to_abs(vcpu, ga);
			if (kvm_is_error_gpa(vcpu->kvm, *pages))
				rc = PGM_ADDRESSING;
		}
		if (rc)
			return trans_exc(vcpu, rc, ga, ar, mode, prot);
		ga += PAGE_SIZE;
		pages++;
		nr_pages--;
	}
	return 0;
}