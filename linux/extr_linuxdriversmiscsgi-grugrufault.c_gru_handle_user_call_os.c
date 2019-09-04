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
struct gru_tlb_fault_handle {int dummy; } ;
struct gru_thread_state {int ts_cbr_au_count; int /*<<< orphan*/  ts_ctxnum; TYPE_1__* ts_gru; scalar_t__ ts_force_cch_reload; } ;
struct TYPE_2__ {int gs_gid; int /*<<< orphan*/  gs_gru_base_vaddr; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int GRU_CBR_AU_SIZE ; 
 int GRU_HANDLE_STRIDE ; 
 int GRU_NUM_CB ; 
 int /*<<< orphan*/  STAT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  call_os ; 
 int get_cb_number (void*) ; 
 void* get_gseg_base_address_cb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct gru_tlb_fault_handle* get_tfh_by_index (TYPE_1__*,int) ; 
 int /*<<< orphan*/  gru_check_context_placement (struct gru_thread_state*) ; 
 int /*<<< orphan*/  gru_dbg (int /*<<< orphan*/ ,char*,unsigned long,int,struct gru_thread_state*) ; 
 struct gru_thread_state* gru_find_lock_gts (unsigned long) ; 
 int /*<<< orphan*/  gru_unlock_gts (struct gru_thread_state*) ; 
 int /*<<< orphan*/  gru_update_cch (struct gru_thread_state*) ; 
 int gru_user_dropin (struct gru_thread_state*,struct gru_tlb_fault_handle*,void*) ; 
 int /*<<< orphan*/  grudev ; 
 int thread_cbr_number (struct gru_thread_state*,int) ; 

int gru_handle_user_call_os(unsigned long cb)
{
	struct gru_tlb_fault_handle *tfh;
	struct gru_thread_state *gts;
	void *cbk;
	int ucbnum, cbrnum, ret = -EINVAL;

	STAT(call_os);

	/* sanity check the cb pointer */
	ucbnum = get_cb_number((void *)cb);
	if ((cb & (GRU_HANDLE_STRIDE - 1)) || ucbnum >= GRU_NUM_CB)
		return -EINVAL;

	gts = gru_find_lock_gts(cb);
	if (!gts)
		return -EINVAL;
	gru_dbg(grudev, "address 0x%lx, gid %d, gts 0x%p\n", cb, gts->ts_gru ? gts->ts_gru->gs_gid : -1, gts);

	if (ucbnum >= gts->ts_cbr_au_count * GRU_CBR_AU_SIZE)
		goto exit;

	gru_check_context_placement(gts);

	/*
	 * CCH may contain stale data if ts_force_cch_reload is set.
	 */
	if (gts->ts_gru && gts->ts_force_cch_reload) {
		gts->ts_force_cch_reload = 0;
		gru_update_cch(gts);
	}

	ret = -EAGAIN;
	cbrnum = thread_cbr_number(gts, ucbnum);
	if (gts->ts_gru) {
		tfh = get_tfh_by_index(gts->ts_gru, cbrnum);
		cbk = get_gseg_base_address_cb(gts->ts_gru->gs_gru_base_vaddr,
				gts->ts_ctxnum, ucbnum);
		ret = gru_user_dropin(gts, tfh, cbk);
	}
exit:
	gru_unlock_gts(gts);
	return ret;
}