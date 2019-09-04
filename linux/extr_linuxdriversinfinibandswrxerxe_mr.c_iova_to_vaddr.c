#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct rxe_mem {scalar_t__ state; TYPE_2__** map; } ;
struct TYPE_4__ {TYPE_1__* buf; } ;
struct TYPE_3__ {size_t size; scalar_t__ addr; } ;

/* Variables and functions */
 scalar_t__ RXE_MEM_STATE_VALID ; 
 int /*<<< orphan*/  lookup_iova (struct rxe_mem*,scalar_t__,int*,int*,size_t*) ; 
 scalar_t__ mem_check_range (struct rxe_mem*,scalar_t__,int) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

void *iova_to_vaddr(struct rxe_mem *mem, u64 iova, int length)
{
	size_t offset;
	int m, n;
	void *addr;

	if (mem->state != RXE_MEM_STATE_VALID) {
		pr_warn("mem not in valid state\n");
		addr = NULL;
		goto out;
	}

	if (!mem->map) {
		addr = (void *)(uintptr_t)iova;
		goto out;
	}

	if (mem_check_range(mem, iova, length)) {
		pr_warn("range violation\n");
		addr = NULL;
		goto out;
	}

	lookup_iova(mem, iova, &m, &n, &offset);

	if (offset + length > mem->map[m]->buf[n].size) {
		pr_warn("crosses page boundary\n");
		addr = NULL;
		goto out;
	}

	addr = (void *)(uintptr_t)mem->map[m]->buf[n].addr + offset;

out:
	return addr;
}