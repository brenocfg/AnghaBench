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
struct rq_wb {int dummy; } ;
struct rq_wait {int dummy; } ;
struct rq_qos {int dummy; } ;
typedef  enum wbt_flags { ____Placeholder_wbt_flags } wbt_flags ;

/* Variables and functions */
 struct rq_wb* RQWB (struct rq_qos*) ; 
 int WBT_TRACKED ; 
 struct rq_wait* get_rq_wait (struct rq_wb*,int) ; 
 int /*<<< orphan*/  wbt_rqw_done (struct rq_wb*,struct rq_wait*,int) ; 

__attribute__((used)) static void __wbt_done(struct rq_qos *rqos, enum wbt_flags wb_acct)
{
	struct rq_wb *rwb = RQWB(rqos);
	struct rq_wait *rqw;

	if (!(wb_acct & WBT_TRACKED))
		return;

	rqw = get_rq_wait(rwb, wb_acct);
	wbt_rqw_done(rwb, rqw, wb_acct);
}