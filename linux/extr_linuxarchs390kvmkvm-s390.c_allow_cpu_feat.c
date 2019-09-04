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
 int /*<<< orphan*/  kvm_s390_available_cpu_feat ; 
 int /*<<< orphan*/  set_bit_inv (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void allow_cpu_feat(unsigned long nr)
{
	set_bit_inv(nr, kvm_s390_available_cpu_feat);
}