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
struct seq_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  asid_new ; 
 int /*<<< orphan*/  asid_next ; 
 int /*<<< orphan*/  asid_reuse ; 
 int /*<<< orphan*/  asid_wrap ; 
 int /*<<< orphan*/  assign_context ; 
 int /*<<< orphan*/  assign_context_failed ; 
 int /*<<< orphan*/  call_os ; 
 int /*<<< orphan*/  call_os_wait_queue ; 
 int /*<<< orphan*/  check_context_retarget_intr ; 
 int /*<<< orphan*/  check_context_unload ; 
 int /*<<< orphan*/  copy_gpa ; 
 int /*<<< orphan*/  flush_tlb ; 
 int /*<<< orphan*/  flush_tlb_gru ; 
 int /*<<< orphan*/  flush_tlb_gru_tgh ; 
 int /*<<< orphan*/  flush_tlb_gru_zero_asid ; 
 int /*<<< orphan*/  free_context ; 
 int /*<<< orphan*/  gms_alloc ; 
 int /*<<< orphan*/  gms_free ; 
 int /*<<< orphan*/  gts_alloc ; 
 int /*<<< orphan*/  gts_double_allocate ; 
 int /*<<< orphan*/  gts_free ; 
 int /*<<< orphan*/  intr ; 
 int /*<<< orphan*/  intr_cbr ; 
 int /*<<< orphan*/  intr_mm_lock_failed ; 
 int /*<<< orphan*/  intr_spurious ; 
 int /*<<< orphan*/  intr_tfh ; 
 int /*<<< orphan*/  load_kernel_context ; 
 int /*<<< orphan*/  load_user_context ; 
 int /*<<< orphan*/  lock_kernel_context ; 
 int /*<<< orphan*/  mesq_noop ; 
 int /*<<< orphan*/  mesq_noop_amo_nacked ; 
 int /*<<< orphan*/  mesq_noop_lb_overflow ; 
 int /*<<< orphan*/  mesq_noop_page_overflow ; 
 int /*<<< orphan*/  mesq_noop_put_nacked ; 
 int /*<<< orphan*/  mesq_noop_qlimit_reached ; 
 int /*<<< orphan*/  mesq_noop_unexpected_error ; 
 int /*<<< orphan*/  mesq_qf_locked ; 
 int /*<<< orphan*/  mesq_qf_noop_not_full ; 
 int /*<<< orphan*/  mesq_qf_switch_head_failed ; 
 int /*<<< orphan*/  mesq_qf_unexpected_error ; 
 int /*<<< orphan*/  mesq_receive ; 
 int /*<<< orphan*/  mesq_receive_none ; 
 int /*<<< orphan*/  mesq_send ; 
 int /*<<< orphan*/  mesq_send_amo_nacked ; 
 int /*<<< orphan*/  mesq_send_failed ; 
 int /*<<< orphan*/  mesq_send_lb_overflow ; 
 int /*<<< orphan*/  mesq_send_put_nacked ; 
 int /*<<< orphan*/  mesq_send_qlimit_reached ; 
 int /*<<< orphan*/  mesq_send_unexpected_error ; 
 int /*<<< orphan*/  mmu_invalidate_page ; 
 int /*<<< orphan*/  mmu_invalidate_range ; 
 int /*<<< orphan*/  nopfn ; 
 int /*<<< orphan*/  printstat (struct seq_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_gpa ; 
 int /*<<< orphan*/  set_context_option ; 
 int /*<<< orphan*/  steal_context_failed ; 
 int /*<<< orphan*/  steal_kernel_context ; 
 int /*<<< orphan*/  steal_user_context ; 
 int /*<<< orphan*/  tfh_stale_on_fault ; 
 int /*<<< orphan*/  tlb_dropin ; 
 int /*<<< orphan*/  tlb_dropin_fail_fmm ; 
 int /*<<< orphan*/  tlb_dropin_fail_idle ; 
 int /*<<< orphan*/  tlb_dropin_fail_invalid ; 
 int /*<<< orphan*/  tlb_dropin_fail_no_asid ; 
 int /*<<< orphan*/  tlb_dropin_fail_no_exception ; 
 int /*<<< orphan*/  tlb_dropin_fail_range_active ; 
 int /*<<< orphan*/  tlb_dropin_fail_upm ; 
 int /*<<< orphan*/  tlb_preload_page ; 
 int /*<<< orphan*/  unlock_kernel_context ; 
 int /*<<< orphan*/  user_exception ; 
 int /*<<< orphan*/  user_flush_tlb ; 
 int /*<<< orphan*/  user_unload_context ; 
 int /*<<< orphan*/  vdata_alloc ; 
 int /*<<< orphan*/  vdata_free ; 

__attribute__((used)) static int statistics_show(struct seq_file *s, void *p)
{
	printstat(s, vdata_alloc);
	printstat(s, vdata_free);
	printstat(s, gts_alloc);
	printstat(s, gts_free);
	printstat(s, gms_alloc);
	printstat(s, gms_free);
	printstat(s, gts_double_allocate);
	printstat(s, assign_context);
	printstat(s, assign_context_failed);
	printstat(s, free_context);
	printstat(s, load_user_context);
	printstat(s, load_kernel_context);
	printstat(s, lock_kernel_context);
	printstat(s, unlock_kernel_context);
	printstat(s, steal_user_context);
	printstat(s, steal_kernel_context);
	printstat(s, steal_context_failed);
	printstat(s, nopfn);
	printstat(s, asid_new);
	printstat(s, asid_next);
	printstat(s, asid_wrap);
	printstat(s, asid_reuse);
	printstat(s, intr);
	printstat(s, intr_cbr);
	printstat(s, intr_tfh);
	printstat(s, intr_spurious);
	printstat(s, intr_mm_lock_failed);
	printstat(s, call_os);
	printstat(s, call_os_wait_queue);
	printstat(s, user_flush_tlb);
	printstat(s, user_unload_context);
	printstat(s, user_exception);
	printstat(s, set_context_option);
	printstat(s, check_context_retarget_intr);
	printstat(s, check_context_unload);
	printstat(s, tlb_dropin);
	printstat(s, tlb_preload_page);
	printstat(s, tlb_dropin_fail_no_asid);
	printstat(s, tlb_dropin_fail_upm);
	printstat(s, tlb_dropin_fail_invalid);
	printstat(s, tlb_dropin_fail_range_active);
	printstat(s, tlb_dropin_fail_idle);
	printstat(s, tlb_dropin_fail_fmm);
	printstat(s, tlb_dropin_fail_no_exception);
	printstat(s, tfh_stale_on_fault);
	printstat(s, mmu_invalidate_range);
	printstat(s, mmu_invalidate_page);
	printstat(s, flush_tlb);
	printstat(s, flush_tlb_gru);
	printstat(s, flush_tlb_gru_tgh);
	printstat(s, flush_tlb_gru_zero_asid);
	printstat(s, copy_gpa);
	printstat(s, read_gpa);
	printstat(s, mesq_receive);
	printstat(s, mesq_receive_none);
	printstat(s, mesq_send);
	printstat(s, mesq_send_failed);
	printstat(s, mesq_noop);
	printstat(s, mesq_send_unexpected_error);
	printstat(s, mesq_send_lb_overflow);
	printstat(s, mesq_send_qlimit_reached);
	printstat(s, mesq_send_amo_nacked);
	printstat(s, mesq_send_put_nacked);
	printstat(s, mesq_qf_locked);
	printstat(s, mesq_qf_noop_not_full);
	printstat(s, mesq_qf_switch_head_failed);
	printstat(s, mesq_qf_unexpected_error);
	printstat(s, mesq_noop_unexpected_error);
	printstat(s, mesq_noop_lb_overflow);
	printstat(s, mesq_noop_qlimit_reached);
	printstat(s, mesq_noop_amo_nacked);
	printstat(s, mesq_noop_put_nacked);
	printstat(s, mesq_noop_page_overflow);
	return 0;
}