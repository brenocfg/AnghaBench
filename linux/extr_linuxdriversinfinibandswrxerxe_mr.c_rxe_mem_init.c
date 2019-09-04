#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct TYPE_5__ {void* rkey; void* lkey; } ;
struct TYPE_6__ {int index; TYPE_1__* pool; } ;
struct rxe_mem {int /*<<< orphan*/  map_shift; int /*<<< orphan*/  type; int /*<<< orphan*/  state; void* rkey; void* lkey; TYPE_2__ ibmr; TYPE_3__ pelem; } ;
struct TYPE_4__ {scalar_t__ type; } ;

/* Variables and functions */
 int IB_ACCESS_REMOTE ; 
 int /*<<< orphan*/  RXE_BUF_PER_MAP ; 
 int /*<<< orphan*/  RXE_MEM_STATE_INVALID ; 
 int /*<<< orphan*/  RXE_MEM_TYPE_NONE ; 
 scalar_t__ RXE_TYPE_MR ; 
 int /*<<< orphan*/  ilog2 (int /*<<< orphan*/ ) ; 
 int rxe_get_key () ; 

__attribute__((used)) static void rxe_mem_init(int access, struct rxe_mem *mem)
{
	u32 lkey = mem->pelem.index << 8 | rxe_get_key();
	u32 rkey = (access & IB_ACCESS_REMOTE) ? lkey : 0;

	if (mem->pelem.pool->type == RXE_TYPE_MR) {
		mem->ibmr.lkey		= lkey;
		mem->ibmr.rkey		= rkey;
	}

	mem->lkey		= lkey;
	mem->rkey		= rkey;
	mem->state		= RXE_MEM_STATE_INVALID;
	mem->type		= RXE_MEM_TYPE_NONE;
	mem->map_shift		= ilog2(RXE_BUF_PER_MAP);
}