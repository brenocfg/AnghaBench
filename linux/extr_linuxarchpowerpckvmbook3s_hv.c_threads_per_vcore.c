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
struct TYPE_2__ {scalar_t__ threads_indep; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 int threads_per_subcore ; 

__attribute__((used)) static int threads_per_vcore(struct kvm *kvm)
{
	if (kvm->arch.threads_indep)
		return 1;
	return threads_per_subcore;
}