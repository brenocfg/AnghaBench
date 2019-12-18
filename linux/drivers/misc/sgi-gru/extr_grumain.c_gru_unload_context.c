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
struct gru_thread_state {int ts_ctxnum; int ts_data_valid; int /*<<< orphan*/  ts_dsr_map; int /*<<< orphan*/  ts_cbr_map; int /*<<< orphan*/  ts_gdata; int /*<<< orphan*/  ts_vma; struct gru_state* ts_gru; } ;
struct gru_state {int /*<<< orphan*/  gs_gru_base_vaddr; } ;
struct gru_context_configuration_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  GRU_GSEG_PAGESIZE ; 
 int /*<<< orphan*/  UGRUADDR (struct gru_thread_state*) ; 
 scalar_t__ cch_deallocate (struct gru_context_configuration_handle*) ; 
 scalar_t__ cch_interrupt_sync (struct gru_context_configuration_handle*) ; 
 struct gru_context_configuration_handle* get_cch (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gru_dbg (int /*<<< orphan*/ ,char*,struct gru_thread_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gru_free_gru_context (struct gru_thread_state*) ; 
 int /*<<< orphan*/  gru_unload_context_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gru_unload_mm_tracker (struct gru_state*,struct gru_thread_state*) ; 
 int /*<<< orphan*/  grudev ; 
 int /*<<< orphan*/  is_kernel_context (struct gru_thread_state*) ; 
 int /*<<< orphan*/  lock_cch_handle (struct gru_context_configuration_handle*) ; 
 int /*<<< orphan*/  unlock_cch_handle (struct gru_context_configuration_handle*) ; 
 int /*<<< orphan*/  zap_vma_ptes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void gru_unload_context(struct gru_thread_state *gts, int savestate)
{
	struct gru_state *gru = gts->ts_gru;
	struct gru_context_configuration_handle *cch;
	int ctxnum = gts->ts_ctxnum;

	if (!is_kernel_context(gts))
		zap_vma_ptes(gts->ts_vma, UGRUADDR(gts), GRU_GSEG_PAGESIZE);
	cch = get_cch(gru->gs_gru_base_vaddr, ctxnum);

	gru_dbg(grudev, "gts %p, cbrmap 0x%lx, dsrmap 0x%lx\n",
		gts, gts->ts_cbr_map, gts->ts_dsr_map);
	lock_cch_handle(cch);
	if (cch_interrupt_sync(cch))
		BUG();

	if (!is_kernel_context(gts))
		gru_unload_mm_tracker(gru, gts);
	if (savestate) {
		gru_unload_context_data(gts->ts_gdata, gru->gs_gru_base_vaddr,
					ctxnum, gts->ts_cbr_map,
					gts->ts_dsr_map);
		gts->ts_data_valid = 1;
	}

	if (cch_deallocate(cch))
		BUG();
	unlock_cch_handle(cch);

	gru_free_gru_context(gts);
}