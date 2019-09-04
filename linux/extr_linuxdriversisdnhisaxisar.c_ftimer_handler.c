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
struct timer_list {int dummy; } ;
struct BCState {int /*<<< orphan*/  Flag; TYPE_3__* cs; } ;
struct TYPE_6__ {scalar_t__ debug; } ;
struct TYPE_4__ {int /*<<< orphan*/  ftimer; } ;
struct TYPE_5__ {TYPE_1__ isar; } ;

/* Variables and functions */
 int /*<<< orphan*/  BC_FLG_FTI_FTS ; 
 int /*<<< orphan*/  BC_FLG_FTI_RUN ; 
 int /*<<< orphan*/  BC_FLG_LL_CONN ; 
 int /*<<< orphan*/  B_LL_CONNECT ; 
 int /*<<< orphan*/  B_LL_OK ; 
 struct BCState* bcs ; 
 int /*<<< orphan*/  debugl1 (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 struct BCState* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 TYPE_2__ hw ; 
 int /*<<< orphan*/  schedule_event (struct BCState*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ftimer_handler(struct timer_list *t) {
	struct BCState *bcs = from_timer(bcs, t, hw.isar.ftimer);
	if (bcs->cs->debug)
		debugl1(bcs->cs, "ftimer flags %04lx",
			bcs->Flag);
	test_and_clear_bit(BC_FLG_FTI_RUN, &bcs->Flag);
	if (test_and_clear_bit(BC_FLG_LL_CONN, &bcs->Flag)) {
		schedule_event(bcs, B_LL_CONNECT);
	}
	if (test_and_clear_bit(BC_FLG_FTI_FTS, &bcs->Flag)) {
		schedule_event(bcs, B_LL_OK);
	}
}