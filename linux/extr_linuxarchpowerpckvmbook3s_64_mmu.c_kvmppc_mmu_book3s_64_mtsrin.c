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
typedef  int ulong ;
typedef  int u64 ;
typedef  int u32 ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*,int,int) ; 
 int /*<<< orphan*/  kvmppc_mmu_book3s_64_slbmte (struct kvm_vcpu*,int,int) ; 

__attribute__((used)) static void kvmppc_mmu_book3s_64_mtsrin(struct kvm_vcpu *vcpu, u32 srnum,
					ulong value)
{
	u64 rb = 0, rs = 0;

	/*
	 * According to Book3 2.01 mtsrin is implemented as:
	 *
	 * The SLB entry specified by (RB)32:35 is loaded from register
	 * RS, as follows.
	 *
	 * SLBE Bit	Source			SLB Field
	 *
	 * 0:31		0x0000_0000		ESID-0:31
	 * 32:35	(RB)32:35		ESID-32:35
	 * 36		0b1			V
	 * 37:61	0x00_0000|| 0b0		VSID-0:24
	 * 62:88	(RS)37:63		VSID-25:51
	 * 89:91	(RS)33:35		Ks Kp N
	 * 92		(RS)36			L ((RS)36 must be 0b0)
	 * 93		0b0			C
	 */

	dprintk("KVM MMU: mtsrin(0x%x, 0x%lx)\n", srnum, value);

	/* ESID = srnum */
	rb |= (srnum & 0xf) << 28;
	/* Set the valid bit */
	rb |= 1 << 27;
	/* Index = ESID */
	rb |= srnum;

	/* VSID = VSID */
	rs |= (value & 0xfffffff) << 12;
	/* flags = flags */
	rs |= ((value >> 28) & 0x7) << 9;

	kvmppc_mmu_book3s_64_slbmte(vcpu, rs, rb);
}