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
typedef  int /*<<< orphan*/  u64 ;
struct rq_qos {int dummy; } ;
struct request_queue {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  enable_state; int /*<<< orphan*/  min_lat_nsec; } ;

/* Variables and functions */
 TYPE_1__* RQWB (struct rq_qos*) ; 
 int /*<<< orphan*/  WBT_STATE_ON_MANUAL ; 
 int /*<<< orphan*/  __wbt_update_limits (TYPE_1__*) ; 
 struct rq_qos* wbt_rq_qos (struct request_queue*) ; 

void wbt_set_min_lat(struct request_queue *q, u64 val)
{
	struct rq_qos *rqos = wbt_rq_qos(q);
	if (!rqos)
		return;
	RQWB(rqos)->min_lat_nsec = val;
	RQWB(rqos)->enable_state = WBT_STATE_ON_MANUAL;
	__wbt_update_limits(RQWB(rqos));
}