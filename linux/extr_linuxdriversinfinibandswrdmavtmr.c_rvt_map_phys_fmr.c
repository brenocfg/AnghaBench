#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* u64 ;
typedef  int u32 ;
struct rvt_lkey_table {int /*<<< orphan*/  lock; } ;
struct TYPE_5__ {int /*<<< orphan*/  count; } ;
struct TYPE_8__ {int max_segs; int page_shift; int length; TYPE_3__** map; void* iova; void* user_base; TYPE_1__ refcount; } ;
struct rvt_fmr {TYPE_4__ mr; } ;
struct rvt_dev_info {struct rvt_lkey_table lkey_table; } ;
struct ib_fmr {int /*<<< orphan*/  device; } ;
struct TYPE_7__ {TYPE_2__* segs; } ;
struct TYPE_6__ {int length; void* vaddr; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int RVT_SEGSZ ; 
 unsigned long atomic_long_read (int /*<<< orphan*/ *) ; 
 struct rvt_dev_info* ib_to_rvt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct rvt_fmr* to_ifmr (struct ib_fmr*) ; 
 int /*<<< orphan*/  trace_rvt_mr_fmr_seg (TYPE_4__*,int,int,void*,int) ; 

int rvt_map_phys_fmr(struct ib_fmr *ibfmr, u64 *page_list,
		     int list_len, u64 iova)
{
	struct rvt_fmr *fmr = to_ifmr(ibfmr);
	struct rvt_lkey_table *rkt;
	unsigned long flags;
	int m, n;
	unsigned long i;
	u32 ps;
	struct rvt_dev_info *rdi = ib_to_rvt(ibfmr->device);

	i = atomic_long_read(&fmr->mr.refcount.count);
	if (i > 2)
		return -EBUSY;

	if (list_len > fmr->mr.max_segs)
		return -EINVAL;

	rkt = &rdi->lkey_table;
	spin_lock_irqsave(&rkt->lock, flags);
	fmr->mr.user_base = iova;
	fmr->mr.iova = iova;
	ps = 1 << fmr->mr.page_shift;
	fmr->mr.length = list_len * ps;
	m = 0;
	n = 0;
	for (i = 0; i < list_len; i++) {
		fmr->mr.map[m]->segs[n].vaddr = (void *)page_list[i];
		fmr->mr.map[m]->segs[n].length = ps;
		trace_rvt_mr_fmr_seg(&fmr->mr, m, n, (void *)page_list[i], ps);
		if (++n == RVT_SEGSZ) {
			m++;
			n = 0;
		}
	}
	spin_unlock_irqrestore(&rkt->lock, flags);
	return 0;
}