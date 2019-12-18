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
struct cardstate {scalar_t__ mstate; int isdn_up; int /*<<< orphan*/  waitqueue; scalar_t__ waiting; } ;

/* Variables and functions */
 int /*<<< orphan*/  MS_INIT ; 
 scalar_t__ MS_LOCKED ; 
 int /*<<< orphan*/  gigaset_free_channels (struct cardstate*) ; 
 int /*<<< orphan*/  gigaset_isdn_start (struct cardstate*) ; 
 int /*<<< orphan*/  schedule_init (struct cardstate*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void do_start(struct cardstate *cs)
{
	gigaset_free_channels(cs);

	if (cs->mstate != MS_LOCKED)
		schedule_init(cs, MS_INIT);

	cs->isdn_up = 1;
	gigaset_isdn_start(cs);

	cs->waiting = 0;
	wake_up(&cs->waitqueue);
}