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
struct cardstate {int dummy; } ;
struct bc_state {int /*<<< orphan*/  at_state; struct cardstate* cs; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_HUP ; 
 int /*<<< orphan*/  gigaset_add_event (struct cardstate*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gigaset_schedule_event (struct cardstate*) ; 

__attribute__((used)) static inline void error_hangup(struct bc_state *bcs)
{
	struct cardstate *cs = bcs->cs;

	gigaset_add_event(cs, &bcs->at_state, EV_HUP, NULL, 0, NULL);
	gigaset_schedule_event(cs);
}