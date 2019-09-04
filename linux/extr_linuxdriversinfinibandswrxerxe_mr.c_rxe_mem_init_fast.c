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
struct rxe_pd {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lkey; int /*<<< orphan*/  rkey; } ;
struct rxe_mem {int max_buf; int /*<<< orphan*/  type; int /*<<< orphan*/  state; struct rxe_pd* pd; TYPE_1__ ibmr; } ;

/* Variables and functions */
 int /*<<< orphan*/  RXE_MEM_STATE_FREE ; 
 int /*<<< orphan*/  RXE_MEM_TYPE_MR ; 
 int rxe_mem_alloc (struct rxe_mem*,int) ; 
 int /*<<< orphan*/  rxe_mem_init (int /*<<< orphan*/ ,struct rxe_mem*) ; 

int rxe_mem_init_fast(struct rxe_pd *pd,
		      int max_pages, struct rxe_mem *mem)
{
	int err;

	rxe_mem_init(0, mem);

	/* In fastreg, we also set the rkey */
	mem->ibmr.rkey = mem->ibmr.lkey;

	err = rxe_mem_alloc(mem, max_pages);
	if (err)
		goto err1;

	mem->pd			= pd;
	mem->max_buf		= max_pages;
	mem->state		= RXE_MEM_STATE_FREE;
	mem->type		= RXE_MEM_TYPE_MR;

	return 0;

err1:
	return err;
}