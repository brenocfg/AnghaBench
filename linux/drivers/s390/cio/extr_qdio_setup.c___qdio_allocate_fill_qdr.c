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
struct TYPE_4__ {int /*<<< orphan*/ * val; } ;
struct qdio_q {TYPE_1__ slsb; scalar_t__ sl; scalar_t__ slib; } ;
struct qdio_irq {TYPE_3__* qdr; } ;
struct TYPE_6__ {TYPE_2__* qdf0; } ;
struct TYPE_5__ {unsigned long sliba; unsigned long sla; unsigned long slsba; int akey; int bkey; int ckey; int dkey; } ;

/* Variables and functions */
 int PAGE_DEFAULT_KEY ; 

__attribute__((used)) static void __qdio_allocate_fill_qdr(struct qdio_irq *irq_ptr,
				     struct qdio_q **irq_ptr_qs,
				     int i, int nr)
{
	irq_ptr->qdr->qdf0[i + nr].sliba =
		(unsigned long)irq_ptr_qs[i]->slib;

	irq_ptr->qdr->qdf0[i + nr].sla =
		(unsigned long)irq_ptr_qs[i]->sl;

	irq_ptr->qdr->qdf0[i + nr].slsba =
		(unsigned long)&irq_ptr_qs[i]->slsb.val[0];

	irq_ptr->qdr->qdf0[i + nr].akey = PAGE_DEFAULT_KEY >> 4;
	irq_ptr->qdr->qdf0[i + nr].bkey = PAGE_DEFAULT_KEY >> 4;
	irq_ptr->qdr->qdf0[i + nr].ckey = PAGE_DEFAULT_KEY >> 4;
	irq_ptr->qdr->qdf0[i + nr].dkey = PAGE_DEFAULT_KEY >> 4;
}