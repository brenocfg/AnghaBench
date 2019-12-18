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
struct hw_perf_event {int state; } ;
struct perf_event {struct hw_perf_event hw; } ;

/* Variables and functions */
 int PERF_HES_STOPPED ; 
 int PERF_HES_UPTODATE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  xgene_perf_disable_event (struct perf_event*) ; 
 int /*<<< orphan*/  xgene_perf_read (struct perf_event*) ; 

__attribute__((used)) static void xgene_perf_stop(struct perf_event *event, int flags)
{
	struct hw_perf_event *hw = &event->hw;

	if (hw->state & PERF_HES_UPTODATE)
		return;

	xgene_perf_disable_event(event);
	WARN_ON_ONCE(hw->state & PERF_HES_STOPPED);
	hw->state |= PERF_HES_STOPPED;

	if (hw->state & PERF_HES_UPTODATE)
		return;

	xgene_perf_read(event);
	hw->state |= PERF_HES_UPTODATE;
}