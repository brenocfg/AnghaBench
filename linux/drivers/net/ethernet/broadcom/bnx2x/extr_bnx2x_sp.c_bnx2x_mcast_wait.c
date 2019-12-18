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
struct TYPE_2__ {scalar_t__ (* wait_comp ) (struct bnx2x*,TYPE_1__*) ;int /*<<< orphan*/  pstate; } ;
struct bnx2x_mcast_obj {TYPE_1__ raw; int /*<<< orphan*/  sched_state; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ bnx2x_state_wait (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct bnx2x*,TYPE_1__*) ; 

__attribute__((used)) static int bnx2x_mcast_wait(struct bnx2x *bp,
			    struct bnx2x_mcast_obj *o)
{
	if (bnx2x_state_wait(bp, o->sched_state, o->raw.pstate) ||
			o->raw.wait_comp(bp, &o->raw))
		return -EBUSY;

	return 0;
}