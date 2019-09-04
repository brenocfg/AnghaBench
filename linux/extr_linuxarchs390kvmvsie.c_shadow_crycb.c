#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_10__ {scalar_t__ dea_wrapping_key_mask; } ;
struct kvm_s390_sie_block {int crycbd; int ecb3; } ;
struct vsie_page {TYPE_3__ crycb; struct kvm_s390_sie_block* scb_o; struct kvm_s390_sie_block scb_s; } ;
struct TYPE_9__ {TYPE_1__* sie_block; } ;
struct kvm_vcpu {TYPE_7__* kvm; TYPE_2__ arch; } ;
typedef  scalar_t__ __u64 ;
typedef  int const __u32 ;
struct TYPE_12__ {TYPE_4__* crycb; } ;
struct TYPE_13__ {TYPE_5__ crypto; } ;
struct TYPE_14__ {TYPE_6__ arch; } ;
struct TYPE_11__ {scalar_t__ dea_wrapping_key_mask; } ;
struct TYPE_8__ {int const crycbd; int ecb3; } ;

/* Variables and functions */
 int BITS_PER_BYTE ; 
 int const CRYCB_FORMAT1 ; 
 int const CRYCB_FORMAT2 ; 
 int ECB3_AES ; 
 int ECB3_DEA ; 
 int const PAGE_MASK ; 
 int READ_ONCE (int) ; 
 int /*<<< orphan*/  bitmap_xor (unsigned long*,unsigned long*,unsigned long*,int) ; 
 scalar_t__ read_guest_real (struct kvm_vcpu*,int const,scalar_t__,int) ; 
 int set_validity_icpt (struct kvm_s390_sie_block*,int) ; 
 int /*<<< orphan*/  test_kvm_facility (TYPE_7__*,int) ; 

__attribute__((used)) static int shadow_crycb(struct kvm_vcpu *vcpu, struct vsie_page *vsie_page)
{
	struct kvm_s390_sie_block *scb_s = &vsie_page->scb_s;
	struct kvm_s390_sie_block *scb_o = vsie_page->scb_o;
	const uint32_t crycbd_o = READ_ONCE(scb_o->crycbd);
	const u32 crycb_addr = crycbd_o & 0x7ffffff8U;
	unsigned long *b1, *b2;
	u8 ecb3_flags;

	scb_s->crycbd = 0;
	if (!(crycbd_o & vcpu->arch.sie_block->crycbd & CRYCB_FORMAT1))
		return 0;
	/* format-1 is supported with message-security-assist extension 3 */
	if (!test_kvm_facility(vcpu->kvm, 76))
		return 0;
	/* we may only allow it if enabled for guest 2 */
	ecb3_flags = scb_o->ecb3 & vcpu->arch.sie_block->ecb3 &
		     (ECB3_AES | ECB3_DEA);
	if (!ecb3_flags)
		return 0;

	if ((crycb_addr & PAGE_MASK) != ((crycb_addr + 128) & PAGE_MASK))
		return set_validity_icpt(scb_s, 0x003CU);
	else if (!crycb_addr)
		return set_validity_icpt(scb_s, 0x0039U);

	/* copy only the wrapping keys */
	if (read_guest_real(vcpu, crycb_addr + 72,
			    vsie_page->crycb.dea_wrapping_key_mask, 56))
		return set_validity_icpt(scb_s, 0x0035U);

	scb_s->ecb3 |= ecb3_flags;
	scb_s->crycbd = ((__u32)(__u64) &vsie_page->crycb) | CRYCB_FORMAT1 |
			CRYCB_FORMAT2;

	/* xor both blocks in one run */
	b1 = (unsigned long *) vsie_page->crycb.dea_wrapping_key_mask;
	b2 = (unsigned long *)
			    vcpu->kvm->arch.crypto.crycb->dea_wrapping_key_mask;
	/* as 56%8 == 0, bitmap_xor won't overwrite any data */
	bitmap_xor(b1, b1, b2, BITS_PER_BYTE * 56);
	return 0;
}