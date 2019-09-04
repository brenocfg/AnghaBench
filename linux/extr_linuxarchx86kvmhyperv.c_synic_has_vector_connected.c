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
struct kvm_vcpu_hv_synic {int /*<<< orphan*/  sint; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int synic_get_sint_vector (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synic_read_sint (struct kvm_vcpu_hv_synic*,int) ; 

__attribute__((used)) static bool synic_has_vector_connected(struct kvm_vcpu_hv_synic *synic,
				      int vector)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(synic->sint); i++) {
		if (synic_get_sint_vector(synic_read_sint(synic, i)) == vector)
			return true;
	}
	return false;
}