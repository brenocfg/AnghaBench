#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct FsmInst {struct Channel* userdata; } ;
struct Channel {TYPE_2__* b_st; scalar_t__ data_open; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* l4l3 ) (TYPE_2__*,int,int /*<<< orphan*/ *) ;} ;
struct TYPE_4__ {TYPE_1__ lli; } ;

/* Variables and functions */
 int DL_RELEASE ; 
 int REQUEST ; 
 int /*<<< orphan*/  lli_bhup_fail (struct FsmInst*,int,void*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
lli_failure_a(struct FsmInst *fi, int event, void *arg)
{
	struct Channel *chanp = fi->userdata;

	chanp->data_open = 0;
	chanp->b_st->lli.l4l3(chanp->b_st, DL_RELEASE | REQUEST, NULL);
	lli_bhup_fail(fi, event, arg);
}