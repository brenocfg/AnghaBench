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
struct TYPE_2__ {int /*<<< orphan*/  msacsr; int /*<<< orphan*/  fcr31; int /*<<< orphan*/ * fpr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLANK () ; 
 int /*<<< orphan*/  COMMENT (char*) ; 
 int /*<<< orphan*/  OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VCPU_FCR31 ; 
 int /*<<< orphan*/  VCPU_FPR0 ; 
 int /*<<< orphan*/  VCPU_FPR1 ; 
 int /*<<< orphan*/  VCPU_FPR10 ; 
 int /*<<< orphan*/  VCPU_FPR11 ; 
 int /*<<< orphan*/  VCPU_FPR12 ; 
 int /*<<< orphan*/  VCPU_FPR13 ; 
 int /*<<< orphan*/  VCPU_FPR14 ; 
 int /*<<< orphan*/  VCPU_FPR15 ; 
 int /*<<< orphan*/  VCPU_FPR16 ; 
 int /*<<< orphan*/  VCPU_FPR17 ; 
 int /*<<< orphan*/  VCPU_FPR18 ; 
 int /*<<< orphan*/  VCPU_FPR19 ; 
 int /*<<< orphan*/  VCPU_FPR2 ; 
 int /*<<< orphan*/  VCPU_FPR20 ; 
 int /*<<< orphan*/  VCPU_FPR21 ; 
 int /*<<< orphan*/  VCPU_FPR22 ; 
 int /*<<< orphan*/  VCPU_FPR23 ; 
 int /*<<< orphan*/  VCPU_FPR24 ; 
 int /*<<< orphan*/  VCPU_FPR25 ; 
 int /*<<< orphan*/  VCPU_FPR26 ; 
 int /*<<< orphan*/  VCPU_FPR27 ; 
 int /*<<< orphan*/  VCPU_FPR28 ; 
 int /*<<< orphan*/  VCPU_FPR29 ; 
 int /*<<< orphan*/  VCPU_FPR3 ; 
 int /*<<< orphan*/  VCPU_FPR30 ; 
 int /*<<< orphan*/  VCPU_FPR31 ; 
 int /*<<< orphan*/  VCPU_FPR4 ; 
 int /*<<< orphan*/  VCPU_FPR5 ; 
 int /*<<< orphan*/  VCPU_FPR6 ; 
 int /*<<< orphan*/  VCPU_FPR7 ; 
 int /*<<< orphan*/  VCPU_FPR8 ; 
 int /*<<< orphan*/  VCPU_FPR9 ; 
 int /*<<< orphan*/  VCPU_MSA_CSR ; 
 TYPE_1__ fpu ; 
 int /*<<< orphan*/  kvm_vcpu_arch ; 

void output_kvm_defines(void)
{
	COMMENT(" KVM/MIPS Specific offsets. ");

	OFFSET(VCPU_FPR0, kvm_vcpu_arch, fpu.fpr[0]);
	OFFSET(VCPU_FPR1, kvm_vcpu_arch, fpu.fpr[1]);
	OFFSET(VCPU_FPR2, kvm_vcpu_arch, fpu.fpr[2]);
	OFFSET(VCPU_FPR3, kvm_vcpu_arch, fpu.fpr[3]);
	OFFSET(VCPU_FPR4, kvm_vcpu_arch, fpu.fpr[4]);
	OFFSET(VCPU_FPR5, kvm_vcpu_arch, fpu.fpr[5]);
	OFFSET(VCPU_FPR6, kvm_vcpu_arch, fpu.fpr[6]);
	OFFSET(VCPU_FPR7, kvm_vcpu_arch, fpu.fpr[7]);
	OFFSET(VCPU_FPR8, kvm_vcpu_arch, fpu.fpr[8]);
	OFFSET(VCPU_FPR9, kvm_vcpu_arch, fpu.fpr[9]);
	OFFSET(VCPU_FPR10, kvm_vcpu_arch, fpu.fpr[10]);
	OFFSET(VCPU_FPR11, kvm_vcpu_arch, fpu.fpr[11]);
	OFFSET(VCPU_FPR12, kvm_vcpu_arch, fpu.fpr[12]);
	OFFSET(VCPU_FPR13, kvm_vcpu_arch, fpu.fpr[13]);
	OFFSET(VCPU_FPR14, kvm_vcpu_arch, fpu.fpr[14]);
	OFFSET(VCPU_FPR15, kvm_vcpu_arch, fpu.fpr[15]);
	OFFSET(VCPU_FPR16, kvm_vcpu_arch, fpu.fpr[16]);
	OFFSET(VCPU_FPR17, kvm_vcpu_arch, fpu.fpr[17]);
	OFFSET(VCPU_FPR18, kvm_vcpu_arch, fpu.fpr[18]);
	OFFSET(VCPU_FPR19, kvm_vcpu_arch, fpu.fpr[19]);
	OFFSET(VCPU_FPR20, kvm_vcpu_arch, fpu.fpr[20]);
	OFFSET(VCPU_FPR21, kvm_vcpu_arch, fpu.fpr[21]);
	OFFSET(VCPU_FPR22, kvm_vcpu_arch, fpu.fpr[22]);
	OFFSET(VCPU_FPR23, kvm_vcpu_arch, fpu.fpr[23]);
	OFFSET(VCPU_FPR24, kvm_vcpu_arch, fpu.fpr[24]);
	OFFSET(VCPU_FPR25, kvm_vcpu_arch, fpu.fpr[25]);
	OFFSET(VCPU_FPR26, kvm_vcpu_arch, fpu.fpr[26]);
	OFFSET(VCPU_FPR27, kvm_vcpu_arch, fpu.fpr[27]);
	OFFSET(VCPU_FPR28, kvm_vcpu_arch, fpu.fpr[28]);
	OFFSET(VCPU_FPR29, kvm_vcpu_arch, fpu.fpr[29]);
	OFFSET(VCPU_FPR30, kvm_vcpu_arch, fpu.fpr[30]);
	OFFSET(VCPU_FPR31, kvm_vcpu_arch, fpu.fpr[31]);

	OFFSET(VCPU_FCR31, kvm_vcpu_arch, fpu.fcr31);
	OFFSET(VCPU_MSA_CSR, kvm_vcpu_arch, fpu.msacsr);
	BLANK();
}