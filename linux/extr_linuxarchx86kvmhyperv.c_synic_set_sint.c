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
typedef  int u64 ;
struct kvm_vcpu_hv_synic {int /*<<< orphan*/ * sint; } ;

/* Variables and functions */
 int HV_SYNIC_FIRST_VALID_VECTOR ; 
 int HV_SYNIC_SINT_MASKED ; 
 int HV_SYNIC_SINT_VECTOR_MASK ; 
 int /*<<< orphan*/  KVM_REQ_SCAN_IOAPIC ; 
 int /*<<< orphan*/  atomic64_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kvm_make_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int synic_read_sint (struct kvm_vcpu_hv_synic*,int) ; 
 int /*<<< orphan*/  synic_to_vcpu (struct kvm_vcpu_hv_synic*) ; 
 int /*<<< orphan*/  synic_update_vector (struct kvm_vcpu_hv_synic*,int) ; 

__attribute__((used)) static int synic_set_sint(struct kvm_vcpu_hv_synic *synic, int sint,
			  u64 data, bool host)
{
	int vector, old_vector;
	bool masked;

	vector = data & HV_SYNIC_SINT_VECTOR_MASK;
	masked = data & HV_SYNIC_SINT_MASKED;

	/*
	 * Valid vectors are 16-255, however, nested Hyper-V attempts to write
	 * default '0x10000' value on boot and this should not #GP. We need to
	 * allow zero-initing the register from host as well.
	 */
	if (vector < HV_SYNIC_FIRST_VALID_VECTOR && !host && !masked)
		return 1;
	/*
	 * Guest may configure multiple SINTs to use the same vector, so
	 * we maintain a bitmap of vectors handled by synic, and a
	 * bitmap of vectors with auto-eoi behavior.  The bitmaps are
	 * updated here, and atomically queried on fast paths.
	 */
	old_vector = synic_read_sint(synic, sint) & HV_SYNIC_SINT_VECTOR_MASK;

	atomic64_set(&synic->sint[sint], data);

	synic_update_vector(synic, old_vector);

	synic_update_vector(synic, vector);

	/* Load SynIC vectors into EOI exit bitmap */
	kvm_make_request(KVM_REQ_SCAN_IOAPIC, synic_to_vcpu(synic));
	return 0;
}