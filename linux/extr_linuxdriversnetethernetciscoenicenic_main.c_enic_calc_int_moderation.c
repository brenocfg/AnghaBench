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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct vnic_rx_bytes_counter {int large_pkt_bytes_cnt; int small_pkt_bytes_cnt; } ;
struct vnic_rq {int /*<<< orphan*/  index; } ;
struct vnic_cq {int tobe_rx_coal_timeval; int /*<<< orphan*/  prev_ts; struct vnic_rx_bytes_counter pkt_size_counter; } ;
struct enic_rx_coal {int small_pkt_range_start; int large_pkt_range_start; int range_end; } ;
struct enic {struct vnic_cq* cq; struct enic_rx_coal rx_coalesce_setting; } ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_2__ {int rx_rate; int range_percent; } ;

/* Variables and functions */
 scalar_t__ ENIC_AIC_TS_BREAK ; 
 int ENIC_MAX_COALESCE_TIMERS ; 
 scalar_t__ UINT_MAX ; 
 size_t enic_cq_rq (struct enic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 scalar_t__ ktime_us_delta (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* mod_table ; 

__attribute__((used)) static void enic_calc_int_moderation(struct enic *enic, struct vnic_rq *rq)
{
	struct enic_rx_coal *rx_coal = &enic->rx_coalesce_setting;
	struct vnic_cq *cq = &enic->cq[enic_cq_rq(enic, rq->index)];
	struct vnic_rx_bytes_counter *pkt_size_counter = &cq->pkt_size_counter;
	int index;
	u32 timer;
	u32 range_start;
	u32 traffic;
	u64 delta;
	ktime_t now = ktime_get();

	delta = ktime_us_delta(now, cq->prev_ts);
	if (delta < ENIC_AIC_TS_BREAK)
		return;
	cq->prev_ts = now;

	traffic = pkt_size_counter->large_pkt_bytes_cnt +
		  pkt_size_counter->small_pkt_bytes_cnt;
	/* The table takes Mbps
	 * traffic *= 8    => bits
	 * traffic *= (10^6 / delta)    => bps
	 * traffic /= 10^6     => Mbps
	 *
	 * Combining, traffic *= (8 / delta)
	 */

	traffic <<= 3;
	traffic = delta > UINT_MAX ? 0 : traffic / (u32)delta;

	for (index = 0; index < ENIC_MAX_COALESCE_TIMERS; index++)
		if (traffic < mod_table[index].rx_rate)
			break;
	range_start = (pkt_size_counter->small_pkt_bytes_cnt >
		       pkt_size_counter->large_pkt_bytes_cnt << 1) ?
		      rx_coal->small_pkt_range_start :
		      rx_coal->large_pkt_range_start;
	timer = range_start + ((rx_coal->range_end - range_start) *
			       mod_table[index].range_percent / 100);
	/* Damping */
	cq->tobe_rx_coal_timeval = (timer + cq->tobe_rx_coal_timeval) >> 1;

	pkt_size_counter->large_pkt_bytes_cnt = 0;
	pkt_size_counter->small_pkt_bytes_cnt = 0;
}