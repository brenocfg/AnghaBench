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
 int RXE_MAX_MR_INDEX ; 
 scalar_t__ RXE_MEM_STATE_VALID ; 
 int RXE_MIN_MR_INDEX ; 
 int lookup_local ; 
 int lookup_remote ; 
 int /*<<< orphan*/  rxe_drop_ref (struct rxe_mem*) ; 
 struct rxe_mem* rxe_pool_get_index (int /*<<< orphan*/ *,int) ; 
 struct rxe_dev* to_rdev (int /*<<< orphan*/ ) ; 

struct rxe_mem *lookup_mem(struct rxe_pd *pd, int access, u32 key,
			   enum lookup_type type)
{
	struct rxe_mem *mem;
	struct rxe_dev *rxe = to_rdev(pd->ibpd.device);
	int index = key >> 8;

	if (index >= RXE_MIN_MR_INDEX && index <= RXE_MAX_MR_INDEX) {
		mem = rxe_pool_get_index(&rxe->mr_pool, index);
		if (!mem)
			goto err1;
	} else {
		goto err1;
	}

	if ((type == lookup_local && mem->lkey != key) ||
	    (type == lookup_remote && mem->rkey != key))
		goto err2;

	if (mem->pd != pd)
		goto err2;

	if (access && !(access & mem->access))
		goto err2;

	if (mem->state != RXE_MEM_STATE_VALID)
		goto err2;

	return mem;

err2:
	rxe_drop_ref(mem);
err1:
	return NULL;
}