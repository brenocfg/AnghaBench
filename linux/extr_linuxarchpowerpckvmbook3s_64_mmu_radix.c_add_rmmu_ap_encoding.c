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
struct kvm_ppc_rmmu_info {int* ap_encodings; } ;
struct TYPE_2__ {int shift; int ap; } ;

/* Variables and functions */
 TYPE_1__* mmu_psize_defs ; 

__attribute__((used)) static void add_rmmu_ap_encoding(struct kvm_ppc_rmmu_info *info,
				 int psize, int *indexp)
{
	if (!mmu_psize_defs[psize].shift)
		return;
	info->ap_encodings[*indexp] = mmu_psize_defs[psize].shift |
		(mmu_psize_defs[psize].ap << 29);
	++(*indexp);
}