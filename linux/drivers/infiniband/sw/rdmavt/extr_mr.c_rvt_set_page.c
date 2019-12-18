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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct TYPE_6__ {int page_shift; int length; int max_segs; TYPE_2__** map; } ;
struct rvt_mr {TYPE_3__ mr; } ;
struct ib_mr {int dummy; } ;
struct TYPE_5__ {TYPE_1__* segs; } ;
struct TYPE_4__ {int length; void* vaddr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int RVT_SEGSZ ; 
 struct rvt_mr* to_imr (struct ib_mr*) ; 
 int /*<<< orphan*/  trace_rvt_mr_page_seg (TYPE_3__*,int,int,void*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int rvt_set_page(struct ib_mr *ibmr, u64 addr)
{
	struct rvt_mr *mr = to_imr(ibmr);
	u32 ps = 1 << mr->mr.page_shift;
	u32 mapped_segs = mr->mr.length >> mr->mr.page_shift;
	int m, n;

	if (unlikely(mapped_segs == mr->mr.max_segs))
		return -ENOMEM;

	m = mapped_segs / RVT_SEGSZ;
	n = mapped_segs % RVT_SEGSZ;
	mr->mr.map[m]->segs[n].vaddr = (void *)addr;
	mr->mr.map[m]->segs[n].length = ps;
	mr->mr.length += ps;
	trace_rvt_mr_page_seg(&mr->mr, m, n, (void *)addr, ps);

	return 0;
}