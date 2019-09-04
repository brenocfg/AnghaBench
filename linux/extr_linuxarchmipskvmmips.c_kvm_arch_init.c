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

/* Variables and functions */
 int EEXIST ; 
 int /*<<< orphan*/  kvm_err (char*) ; 
 scalar_t__ kvm_mips_callbacks ; 
 int kvm_mips_emulation_init (scalar_t__*) ; 

int kvm_arch_init(void *opaque)
{
	if (kvm_mips_callbacks) {
		kvm_err("kvm: module already exists\n");
		return -EEXIST;
	}

	return kvm_mips_emulation_init(&kvm_mips_callbacks);
}