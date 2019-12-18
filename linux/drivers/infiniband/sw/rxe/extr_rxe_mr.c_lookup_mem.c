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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;
struct rxe_pd {TYPE_1__ ibpd; } ;
struct rxe_mem {int lkey; int rkey; int access; scalar_t__ state; struct rxe_pd* pd; } ;
struct rxe_dev {int /*<<< orphan*/  mr_pool; } ;
typedef  enum lookup_type { ____Placeholder_lookup_type } lookup_type ;

/* Variables and functions */
 scalar_t__ RXE_MEM_STATE_VALID ; 
 int lookup_local ; 
 int lookup_remote ; 
 int /*<<< orphan*/  rxe_drop_ref (struct rxe_mem*) ; 
 struct rxe_mem* rxe_pool_get_index (int /*<<< orphan*/ *,int) ; 
 struct rxe_dev* to_rdev (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

struct rxe_mem *lookup_mem(struct rxe_pd *pd, int access, u32 key,
			   enum lookup_type type)
{
	struct rxe_mem *mem;
	struct rxe_dev *rxe = to_rdev(pd->ibpd.device);
	int index = key >> 8;

	mem = rxe_pool_get_index(&rxe->mr_pool, index);
	if (!mem)
		return NULL;

	if (unlikely((type == lookup_local && mem->lkey != key) ||
		     (type == lookup_remote && mem->rkey != key) ||
		     mem->pd != pd ||
		     (access && !(access & mem->access)) ||
		     mem->state != RXE_MEM_STATE_VALID)) {
		rxe_drop_ref(mem);
		mem = NULL;
	}

	return mem;
}