#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned long long tstamp; int util_state; long long* times; } ;
struct spu_context {TYPE_1__ stats; struct spu* spu; int /*<<< orphan*/  state_mutex; } ;
struct TYPE_5__ {long long* times; int util_state; unsigned long long tstamp; } ;
struct spu {int node; TYPE_2__ stats; } ;
typedef  enum spu_utilization_state { ____Placeholder_spu_utilization_state } spu_utilization_state ;
struct TYPE_6__ {int /*<<< orphan*/  busy_spus; } ;

/* Variables and functions */
 int SPU_UTIL_USER ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 TYPE_3__* cbe_spu_info ; 
 unsigned long long ktime_get_ns () ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 

void spuctx_switch_state(struct spu_context *ctx,
		enum spu_utilization_state new_state)
{
	unsigned long long curtime;
	signed long long delta;
	struct spu *spu;
	enum spu_utilization_state old_state;
	int node;

	curtime = ktime_get_ns();
	delta = curtime - ctx->stats.tstamp;

	WARN_ON(!mutex_is_locked(&ctx->state_mutex));
	WARN_ON(delta < 0);

	spu = ctx->spu;
	old_state = ctx->stats.util_state;
	ctx->stats.util_state = new_state;
	ctx->stats.tstamp = curtime;

	/*
	 * Update the physical SPU utilization statistics.
	 */
	if (spu) {
		ctx->stats.times[old_state] += delta;
		spu->stats.times[old_state] += delta;
		spu->stats.util_state = new_state;
		spu->stats.tstamp = curtime;
		node = spu->node;
		if (old_state == SPU_UTIL_USER)
			atomic_dec(&cbe_spu_info[node].busy_spus);
		if (new_state == SPU_UTIL_USER)
			atomic_inc(&cbe_spu_info[node].busy_spus);
	}
}