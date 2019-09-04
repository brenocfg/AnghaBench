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
struct FsmInst {struct Channel* userdata; } ;
struct Channel {scalar_t__ chan; TYPE_1__* cs; scalar_t__ Flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* cardmsg ) (TYPE_1__*,int /*<<< orphan*/ ,void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FsmChangeState (struct FsmInst*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MDL_INFO_REL ; 
 int /*<<< orphan*/  ST_NULL ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static inline void
lli_close(struct FsmInst *fi)
{
	struct Channel *chanp = fi->userdata;

	FsmChangeState(fi, ST_NULL);
	chanp->Flags = 0;
	chanp->cs->cardmsg(chanp->cs, MDL_INFO_REL, (void *) (long)chanp->chan);
}