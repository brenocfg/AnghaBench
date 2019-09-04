#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_3__ {scalar_t__ timer_start1; scalar_t__ cpu_interval; scalar_t__ max_latency; scalar_t__ min_latency; int /*<<< orphan*/  io_interval; int /*<<< orphan*/  latency_sum; int /*<<< orphan*/  interrupt_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  TIMER_NUM ; 
 int /*<<< orphan*/  init_latency_info (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__ li ; 
 scalar_t__ read_c0_cvmcount () ; 
 int reset_stats ; 
 int /*<<< orphan*/  start_timer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t cvm_oct_ciu_timer_interrupt(int cpl, void *dev_id)
{
	u64 last_latency;
	u64 last_int_cnt;

	if (reset_stats) {
		init_latency_info(&li, 0);
		reset_stats = false;
	} else {
		last_int_cnt = read_c0_cvmcount();
		last_latency = last_int_cnt - (li.timer_start1 + li.cpu_interval);
		li.interrupt_cnt++;
		li.latency_sum += last_latency;
		if (last_latency > li.max_latency)
			li.max_latency = last_latency;
		if (last_latency < li.min_latency)
			li.min_latency = last_latency;
	}
	start_timer(TIMER_NUM, li.io_interval);
	return IRQ_HANDLED;
}