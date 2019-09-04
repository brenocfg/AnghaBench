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
struct rxe_pd {int dummy; } ;
struct rxe_mem {int access; int /*<<< orphan*/  type; int /*<<< orphan*/  state; struct rxe_pd* pd; } ;

/* Variables and functions */
 int /*<<< orphan*/  RXE_MEM_STATE_VALID ; 
 int /*<<< orphan*/  RXE_MEM_TYPE_DMA ; 
 int /*<<< orphan*/  rxe_mem_init (int,struct rxe_mem*) ; 

int rxe_mem_init_dma(struct rxe_pd *pd,
		     int access, struct rxe_mem *mem)
{
	rxe_mem_init(access, mem);

	mem->pd			= pd;
	mem->access		= access;
	mem->state		= RXE_MEM_STATE_VALID;
	mem->type		= RXE_MEM_TYPE_DMA;

	return 0;
}