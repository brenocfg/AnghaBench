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
struct siw_mr {struct siw_mem* mem; } ;
struct siw_mem {int stag; TYPE_1__* sdev; scalar_t__ stag_valid; } ;
struct TYPE_2__ {int /*<<< orphan*/  mem_xa; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  siw_mem_put (struct siw_mem*) ; 
 int /*<<< orphan*/  smp_mb () ; 
 struct siw_mem* xa_erase (int /*<<< orphan*/ *,int) ; 

void siw_mr_drop_mem(struct siw_mr *mr)
{
	struct siw_mem *mem = mr->mem, *found;

	mem->stag_valid = 0;

	/* make STag invalid visible asap */
	smp_mb();

	found = xa_erase(&mem->sdev->mem_xa, mem->stag >> 8);
	WARN_ON(found != mem);
	siw_mem_put(mem);
}