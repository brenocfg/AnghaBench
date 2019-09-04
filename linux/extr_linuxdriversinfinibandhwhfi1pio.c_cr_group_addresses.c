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
typedef  size_t u32 ;
struct send_context {int hw_context; size_t node; TYPE_3__* dd; int /*<<< orphan*/ * hw_free; int /*<<< orphan*/  group; } ;
struct credit_return {int dummy; } ;
typedef  unsigned long dma_addr_t ;
struct TYPE_6__ {TYPE_2__* cr_base; } ;
struct TYPE_5__ {scalar_t__ dma; TYPE_1__* va; } ;
struct TYPE_4__ {int /*<<< orphan*/ * cr; } ;

/* Variables and functions */
 size_t group_context (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cr_group_addresses(struct send_context *sc, dma_addr_t *dma)
{
	u32 gc = group_context(sc->hw_context, sc->group);
	u32 index = sc->hw_context & 0x7;

	sc->hw_free = &sc->dd->cr_base[sc->node].va[gc].cr[index];
	*dma = (unsigned long)
	       &((struct credit_return *)sc->dd->cr_base[sc->node].dma)[gc];
}