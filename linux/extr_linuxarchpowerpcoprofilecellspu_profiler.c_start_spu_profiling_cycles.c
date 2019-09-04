#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_5__ {int /*<<< orphan*/  function; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  DEFAULT_TIMER_EXPIRE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 int SPUS_PER_NODE ; 
 int /*<<< orphan*/  TICK_NSEC ; 
 int TRACE_ARRAY_SIZE ; 
 int /*<<< orphan*/  hrtimer_init (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrtimer_set_expires (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrtimer_start (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  profile_spus ; 
 int /*<<< orphan*/  profiling_interval ; 
 int /*<<< orphan*/  samples ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int spu_prof_running ; 
 int /*<<< orphan*/  spu_work ; 
 TYPE_1__ timer ; 

int start_spu_profiling_cycles(unsigned int cycles_reset)
{
	ktime_t kt;

	pr_debug("timer resolution: %lu\n", TICK_NSEC);
	kt = profiling_interval;
	hrtimer_init(&timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	hrtimer_set_expires(&timer, kt);
	timer.function = profile_spus;

	/* Allocate arrays for collecting SPU PC samples */
	samples = kcalloc(SPUS_PER_NODE * TRACE_ARRAY_SIZE, sizeof(u32),
			  GFP_KERNEL);

	if (!samples)
		return -ENOMEM;

	spu_prof_running = 1;
	hrtimer_start(&timer, kt, HRTIMER_MODE_REL);
	schedule_delayed_work(&spu_work, DEFAULT_TIMER_EXPIRE);

	return 0;
}