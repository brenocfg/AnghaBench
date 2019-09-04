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
struct s390_io_adapter {int dummy; } ;
struct TYPE_2__ {struct s390_io_adapter** adapters; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 unsigned int MAX_S390_IO_ADAPTERS ; 

__attribute__((used)) static struct s390_io_adapter *get_io_adapter(struct kvm *kvm, unsigned int id)
{
	if (id >= MAX_S390_IO_ADAPTERS)
		return NULL;
	return kvm->arch.adapters[id];
}