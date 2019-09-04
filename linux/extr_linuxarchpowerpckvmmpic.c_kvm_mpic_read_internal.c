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
typedef  int /*<<< orphan*/  u32 ;
struct openpic {int num_mmio_regions; struct mem_reg** mmio_regions; } ;
struct mem_reg {scalar_t__ start_addr; scalar_t__ size; int (* read ) (struct openpic*,scalar_t__,int /*<<< orphan*/ *) ;} ;
typedef  scalar_t__ gpa_t ;

/* Variables and functions */
 int ENXIO ; 
 int stub1 (struct openpic*,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int kvm_mpic_read_internal(struct openpic *opp, gpa_t addr, u32 *ptr)
{
	int i;

	for (i = 0; i < opp->num_mmio_regions; i++) {
		const struct mem_reg *mr = opp->mmio_regions[i];

		if (mr->start_addr > addr || addr >= mr->start_addr + mr->size)
			continue;

		return mr->read(opp, addr - mr->start_addr, ptr);
	}

	return -ENXIO;
}