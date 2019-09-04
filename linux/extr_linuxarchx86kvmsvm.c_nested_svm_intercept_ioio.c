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
typedef  unsigned int u8 ;
typedef  scalar_t__ u64 ;
typedef  int u16 ;
struct TYPE_6__ {unsigned long long intercept; scalar_t__ vmcb_iopm; } ;
struct vcpu_svm {int /*<<< orphan*/  vcpu; TYPE_3__ nested; TYPE_2__* vmcb; } ;
struct TYPE_4__ {int exit_info_1; } ;
struct TYPE_5__ {TYPE_1__ control; } ;

/* Variables and functions */
 unsigned long long INTERCEPT_IOIO_PROT ; 
 int NESTED_EXIT_DONE ; 
 int NESTED_EXIT_HOST ; 
 unsigned int SVM_IOIO_SIZE_MASK ; 
 unsigned int SVM_IOIO_SIZE_SHIFT ; 
 scalar_t__ kvm_vcpu_read_guest (int /*<<< orphan*/ *,scalar_t__,int*,unsigned int) ; 

__attribute__((used)) static int nested_svm_intercept_ioio(struct vcpu_svm *svm)
{
	unsigned port, size, iopm_len;
	u16 val, mask;
	u8 start_bit;
	u64 gpa;

	if (!(svm->nested.intercept & (1ULL << INTERCEPT_IOIO_PROT)))
		return NESTED_EXIT_HOST;

	port = svm->vmcb->control.exit_info_1 >> 16;
	size = (svm->vmcb->control.exit_info_1 & SVM_IOIO_SIZE_MASK) >>
		SVM_IOIO_SIZE_SHIFT;
	gpa  = svm->nested.vmcb_iopm + (port / 8);
	start_bit = port % 8;
	iopm_len = (start_bit + size > 8) ? 2 : 1;
	mask = (0xf >> (4 - size)) << start_bit;
	val = 0;

	if (kvm_vcpu_read_guest(&svm->vcpu, gpa, &val, iopm_len))
		return NESTED_EXIT_DONE;

	return (val & mask) ? NESTED_EXIT_DONE : NESTED_EXIT_HOST;
}