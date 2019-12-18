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
struct vm_area_struct {struct gru_vma_data* vm_private_data; } ;
struct gru_vma_data {int /*<<< orphan*/  vd_lock; int /*<<< orphan*/  vd_head; int /*<<< orphan*/  vd_user_options; int /*<<< orphan*/  vd_tlb_preload_count; int /*<<< orphan*/  vd_dsr_au_count; int /*<<< orphan*/  vd_cbr_au_count; } ;
struct gru_thread_state {int /*<<< orphan*/  ts_next; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct gru_thread_state*) ; 
 int /*<<< orphan*/  STAT (int /*<<< orphan*/ ) ; 
 struct gru_thread_state* gru_alloc_gts (struct vm_area_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gru_dbg (int /*<<< orphan*/ ,char*,struct vm_area_struct*,struct gru_thread_state*) ; 
 struct gru_thread_state* gru_find_current_gts_nolock (struct gru_vma_data*,int) ; 
 int /*<<< orphan*/  grudev ; 
 int /*<<< orphan*/  gts_double_allocate ; 
 int /*<<< orphan*/  gts_drop (struct gru_thread_state*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct gru_thread_state *gru_alloc_thread_state(struct vm_area_struct *vma,
					int tsid)
{
	struct gru_vma_data *vdata = vma->vm_private_data;
	struct gru_thread_state *gts, *ngts;

	gts = gru_alloc_gts(vma, vdata->vd_cbr_au_count,
			    vdata->vd_dsr_au_count,
			    vdata->vd_tlb_preload_count,
			    vdata->vd_user_options, tsid);
	if (IS_ERR(gts))
		return gts;

	spin_lock(&vdata->vd_lock);
	ngts = gru_find_current_gts_nolock(vdata, tsid);
	if (ngts) {
		gts_drop(gts);
		gts = ngts;
		STAT(gts_double_allocate);
	} else {
		list_add(&gts->ts_next, &vdata->vd_head);
	}
	spin_unlock(&vdata->vd_lock);
	gru_dbg(grudev, "vma %p, gts %p\n", vma, gts);
	return gts;
}