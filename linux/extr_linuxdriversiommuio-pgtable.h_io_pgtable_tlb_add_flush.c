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
struct TYPE_4__ {TYPE_1__* tlb; } ;
struct io_pgtable {int /*<<< orphan*/  cookie; TYPE_2__ cfg; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* tlb_add_flush ) (unsigned long,size_t,size_t,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (unsigned long,size_t,size_t,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void io_pgtable_tlb_add_flush(struct io_pgtable *iop,
		unsigned long iova, size_t size, size_t granule, bool leaf)
{
	iop->cfg.tlb->tlb_add_flush(iova, size, granule, leaf, iop->cookie);
}