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
struct si_sm_io {unsigned long addr_data; int regspacing; int /*<<< orphan*/  regsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  release_mem_region (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mem_region_cleanup(struct si_sm_io *io, int num)
{
	unsigned long addr = io->addr_data;
	int idx;

	for (idx = 0; idx < num; idx++)
		release_mem_region(addr + idx * io->regspacing,
				   io->regsize);
}