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
struct rq_wb {struct request* sync_cookie; int /*<<< orphan*/  last_comp; scalar_t__ sync_issue; } ;
struct rq_qos {int dummy; } ;
struct request {int dummy; } ;

/* Variables and functions */
 struct rq_wb* RQWB (struct rq_qos*) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __wbt_done (struct rq_qos*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wb_timestamp (struct rq_wb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wbt_clear_state (struct request*) ; 
 int /*<<< orphan*/  wbt_flags (struct request*) ; 
 scalar_t__ wbt_is_read (struct request*) ; 
 int /*<<< orphan*/  wbt_is_tracked (struct request*) ; 

__attribute__((used)) static void wbt_done(struct rq_qos *rqos, struct request *rq)
{
	struct rq_wb *rwb = RQWB(rqos);

	if (!wbt_is_tracked(rq)) {
		if (rwb->sync_cookie == rq) {
			rwb->sync_issue = 0;
			rwb->sync_cookie = NULL;
		}

		if (wbt_is_read(rq))
			wb_timestamp(rwb, &rwb->last_comp);
	} else {
		WARN_ON_ONCE(rq == rwb->sync_cookie);
		__wbt_done(rqos, wbt_flags(rq));
	}
	wbt_clear_state(rq);
}