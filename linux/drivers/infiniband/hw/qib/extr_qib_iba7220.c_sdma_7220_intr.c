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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int current_state; } ;
struct qib_pportdata {int /*<<< orphan*/  sdma_lock; TYPE_1__ sdma_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  __qib_sdma_intr (struct qib_pportdata*) ; 
 int /*<<< orphan*/  __qib_sdma_process_event (struct qib_pportdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_sdma_event_e20_hw_started ; 
 int /*<<< orphan*/  qib_sdma_event_e60_hw_halted ; 
#define  qib_sdma_state_s00_hw_down 134 
#define  qib_sdma_state_s10_hw_start_up_wait 133 
#define  qib_sdma_state_s20_idle 132 
#define  qib_sdma_state_s30_sw_clean_up_wait 131 
#define  qib_sdma_state_s40_hw_clean_up_wait 130 
#define  qib_sdma_state_s50_hw_halt_wait 129 
#define  qib_sdma_state_s99_running 128 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void sdma_7220_intr(struct qib_pportdata *ppd, u64 istat)
{
	unsigned long flags;

	spin_lock_irqsave(&ppd->sdma_lock, flags);

	switch (ppd->sdma_state.current_state) {
	case qib_sdma_state_s00_hw_down:
		break;

	case qib_sdma_state_s10_hw_start_up_wait:
		__qib_sdma_process_event(ppd, qib_sdma_event_e20_hw_started);
		break;

	case qib_sdma_state_s20_idle:
		break;

	case qib_sdma_state_s30_sw_clean_up_wait:
		break;

	case qib_sdma_state_s40_hw_clean_up_wait:
		break;

	case qib_sdma_state_s50_hw_halt_wait:
		__qib_sdma_process_event(ppd, qib_sdma_event_e60_hw_halted);
		break;

	case qib_sdma_state_s99_running:
		/* too chatty to print here */
		__qib_sdma_intr(ppd);
		break;
	}
	spin_unlock_irqrestore(&ppd->sdma_lock, flags);
}