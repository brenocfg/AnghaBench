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
struct TYPE_2__ {int /*<<< orphan*/  upm_tlbmiss; } ;
struct gru_thread_state {int /*<<< orphan*/  ts_gru; TYPE_1__ ustats; struct gru_mm_struct* ts_gms; } ;
struct gru_mm_struct {int /*<<< orphan*/  ms_range_active; int /*<<< orphan*/  ms_wait_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  STAT (int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  call_os_wait_queue ; 
 int gru_try_dropin (int /*<<< orphan*/ ,struct gru_thread_state*,struct gru_tlb_fault_handle*,void*) ; 
 int /*<<< orphan*/  prefetchw (struct gru_tlb_fault_handle*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int gru_user_dropin(struct gru_thread_state *gts,
			   struct gru_tlb_fault_handle *tfh,
			   void *cb)
{
	struct gru_mm_struct *gms = gts->ts_gms;
	int ret;

	gts->ustats.upm_tlbmiss++;
	while (1) {
		wait_event(gms->ms_wait_queue,
			   atomic_read(&gms->ms_range_active) == 0);
		prefetchw(tfh);	/* Helps on hdw, required for emulator */
		ret = gru_try_dropin(gts->ts_gru, gts, tfh, cb);
		if (ret <= 0)
			return ret;
		STAT(call_os_wait_queue);
	}
}