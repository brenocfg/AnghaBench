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
struct rq_depth {int scaled_max; scalar_t__ scale_step; } ;
struct rq_wb {struct rq_depth rq_depth; } ;

/* Variables and functions */
 int /*<<< orphan*/  calc_wb_limits (struct rq_wb*) ; 
 int /*<<< orphan*/  rq_depth_calc_max_depth (struct rq_depth*) ; 
 int /*<<< orphan*/  rwb_wake_all (struct rq_wb*) ; 

__attribute__((used)) static void __wbt_update_limits(struct rq_wb *rwb)
{
	struct rq_depth *rqd = &rwb->rq_depth;

	rqd->scale_step = 0;
	rqd->scaled_max = false;

	rq_depth_calc_max_depth(rqd);
	calc_wb_limits(rwb);

	rwb_wake_all(rwb);
}