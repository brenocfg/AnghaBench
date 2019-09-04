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
struct TYPE_2__ {int /*<<< orphan*/  exclude_user; int /*<<< orphan*/  exclude_kernel; } ;
struct perf_event {TYPE_1__ attr; } ;
struct bts_ctx {int /*<<< orphan*/  state; int /*<<< orphan*/  handle; } ;
struct bts_buffer {int /*<<< orphan*/  snapshot; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCH_PERFMON_EVENTSEL_INT ; 
 int /*<<< orphan*/  ARCH_PERFMON_EVENTSEL_OS ; 
 int /*<<< orphan*/  ARCH_PERFMON_EVENTSEL_USR ; 
 int /*<<< orphan*/  BTS_STATE_ACTIVE ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bts_config_buffer (struct bts_buffer*) ; 
 int /*<<< orphan*/  bts_ctx ; 
 int /*<<< orphan*/  intel_pmu_enable_bts (int /*<<< orphan*/ ) ; 
 struct bts_buffer* perf_get_aux (int /*<<< orphan*/ *) ; 
 struct bts_ctx* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void __bts_event_start(struct perf_event *event)
{
	struct bts_ctx *bts = this_cpu_ptr(&bts_ctx);
	struct bts_buffer *buf = perf_get_aux(&bts->handle);
	u64 config = 0;

	if (!buf->snapshot)
		config |= ARCH_PERFMON_EVENTSEL_INT;
	if (!event->attr.exclude_kernel)
		config |= ARCH_PERFMON_EVENTSEL_OS;
	if (!event->attr.exclude_user)
		config |= ARCH_PERFMON_EVENTSEL_USR;

	bts_config_buffer(buf);

	/*
	 * local barrier to make sure that ds configuration made it
	 * before we enable BTS and bts::state goes ACTIVE
	 */
	wmb();

	/* INACTIVE/STOPPED -> ACTIVE */
	WRITE_ONCE(bts->state, BTS_STATE_ACTIVE);

	intel_pmu_enable_bts(config);

}