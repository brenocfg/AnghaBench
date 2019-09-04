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
typedef  int u64 ;
struct hw_perf_event {int idx; int config_base; int /*<<< orphan*/  config; } ;
struct perf_event {struct hw_perf_event hw; } ;
struct p4_event_bind {int* escr_msr; int /*<<< orphan*/  opcode; } ;

/* Variables and functions */
 int P4_CCCR_ENABLE ; 
 int P4_CCCR_RESERVED ; 
 int P4_ESCR_EVENT (int /*<<< orphan*/ ) ; 
 int P4_ESCR_EVENT_MASK ; 
 int /*<<< orphan*/  P4_OPCODE_EVNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  p4_clear_ht_bit (int /*<<< orphan*/ ) ; 
 int p4_config_unpack_cccr (int /*<<< orphan*/ ) ; 
 int p4_config_unpack_escr (int /*<<< orphan*/ ) ; 
 unsigned int p4_config_unpack_event (int /*<<< orphan*/ ) ; 
 struct p4_event_bind* p4_event_bind_map ; 
 int p4_ht_config_thread (int /*<<< orphan*/ ) ; 
 int p4_is_event_cascaded (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p4_pmu_enable_pebs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrmsrl_safe (int,int) ; 

__attribute__((used)) static void p4_pmu_enable_event(struct perf_event *event)
{
	struct hw_perf_event *hwc = &event->hw;
	int thread = p4_ht_config_thread(hwc->config);
	u64 escr_conf = p4_config_unpack_escr(p4_clear_ht_bit(hwc->config));
	unsigned int idx = p4_config_unpack_event(hwc->config);
	struct p4_event_bind *bind;
	u64 escr_addr, cccr;

	bind = &p4_event_bind_map[idx];
	escr_addr = bind->escr_msr[thread];

	/*
	 * - we dont support cascaded counters yet
	 * - and counter 1 is broken (erratum)
	 */
	WARN_ON_ONCE(p4_is_event_cascaded(hwc->config));
	WARN_ON_ONCE(hwc->idx == 1);

	/* we need a real Event value */
	escr_conf &= ~P4_ESCR_EVENT_MASK;
	escr_conf |= P4_ESCR_EVENT(P4_OPCODE_EVNT(bind->opcode));

	cccr = p4_config_unpack_cccr(hwc->config);

	/*
	 * it could be Cache event so we need to write metrics
	 * into additional MSRs
	 */
	p4_pmu_enable_pebs(hwc->config);

	(void)wrmsrl_safe(escr_addr, escr_conf);
	(void)wrmsrl_safe(hwc->config_base,
				(cccr & ~P4_CCCR_RESERVED) | P4_CCCR_ENABLE);
}