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
struct vm_area_struct {int dummy; } ;
struct gru_thread_state {int ts_cbr_au_count; int ts_dsr_au_count; unsigned char ts_tlb_preload_count; int ts_user_options; int ts_user_blade_id; int ts_user_chiplet_id; int ts_tsid; int ts_tlb_int_select; int ts_cch_req_slice; struct gru_mm_struct* ts_gms; struct vm_area_struct* ts_vma; int /*<<< orphan*/  ts_mm; int /*<<< orphan*/  ts_sizeavail; int /*<<< orphan*/  ts_ctxnum; int /*<<< orphan*/  ts_ctxlock; int /*<<< orphan*/  ts_refcnt; } ;
struct gru_mm_struct {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 int CBR_BYTES (int) ; 
 int DSR_BYTES (int) ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct gru_thread_state* ERR_CAST (struct gru_mm_struct*) ; 
 struct gru_thread_state* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GRU_SIZEAVAIL (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct gru_mm_struct*) ; 
 int /*<<< orphan*/  NULLCTX ; 
 int /*<<< orphan*/  PAGE_SHIFT ; 
 int /*<<< orphan*/  STAT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  gru_dbg (int /*<<< orphan*/ ,char*,struct gru_thread_state*) ; 
 struct gru_mm_struct* gru_register_mmu_notifier () ; 
 int /*<<< orphan*/  grudev ; 
 int /*<<< orphan*/  gts_alloc ; 
 int /*<<< orphan*/  gts_drop (struct gru_thread_state*) ; 
 struct gru_thread_state* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct gru_thread_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

struct gru_thread_state *gru_alloc_gts(struct vm_area_struct *vma,
		int cbr_au_count, int dsr_au_count,
		unsigned char tlb_preload_count, int options, int tsid)
{
	struct gru_thread_state *gts;
	struct gru_mm_struct *gms;
	int bytes;

	bytes = DSR_BYTES(dsr_au_count) + CBR_BYTES(cbr_au_count);
	bytes += sizeof(struct gru_thread_state);
	gts = kmalloc(bytes, GFP_KERNEL);
	if (!gts)
		return ERR_PTR(-ENOMEM);

	STAT(gts_alloc);
	memset(gts, 0, sizeof(struct gru_thread_state)); /* zero out header */
	atomic_set(&gts->ts_refcnt, 1);
	mutex_init(&gts->ts_ctxlock);
	gts->ts_cbr_au_count = cbr_au_count;
	gts->ts_dsr_au_count = dsr_au_count;
	gts->ts_tlb_preload_count = tlb_preload_count;
	gts->ts_user_options = options;
	gts->ts_user_blade_id = -1;
	gts->ts_user_chiplet_id = -1;
	gts->ts_tsid = tsid;
	gts->ts_ctxnum = NULLCTX;
	gts->ts_tlb_int_select = -1;
	gts->ts_cch_req_slice = -1;
	gts->ts_sizeavail = GRU_SIZEAVAIL(PAGE_SHIFT);
	if (vma) {
		gts->ts_mm = current->mm;
		gts->ts_vma = vma;
		gms = gru_register_mmu_notifier();
		if (IS_ERR(gms))
			goto err;
		gts->ts_gms = gms;
	}

	gru_dbg(grudev, "alloc gts %p\n", gts);
	return gts;

err:
	gts_drop(gts);
	return ERR_CAST(gms);
}