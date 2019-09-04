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
struct Channel {int /*<<< orphan*/  proc; TYPE_2__* d_st; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* l4l3 ) (TYPE_2__*,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {TYPE_1__ lli; } ;

/* Variables and functions */
 int CC_SETUP ; 
 int /*<<< orphan*/  FsmChangeState (struct FsmInst*,int /*<<< orphan*/ ) ; 
 int RESPONSE ; 
 int /*<<< orphan*/  ST_IN_WAIT_CONN_ACK ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lli_send_dconnect(struct FsmInst *fi, int event, void *arg)
{
	struct Channel *chanp = fi->userdata;

	FsmChangeState(fi, ST_IN_WAIT_CONN_ACK);
	chanp->d_st->lli.l4l3(chanp->d_st, CC_SETUP | RESPONSE, chanp->proc);
}