#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int features; int /*<<< orphan*/  (* statcallb ) (TYPE_2__*) ;} ;
struct IsdnCardState {TYPE_1__ iif; int /*<<< orphan*/  myid; } ;
struct TYPE_5__ {int /*<<< orphan*/  command; int /*<<< orphan*/  driver; } ;
typedef  TYPE_2__ isdn_ctrl ;

/* Variables and functions */
 int /*<<< orphan*/  ISDN_STAT_RUN ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

int ll_run(struct IsdnCardState *cs, int addfeatures)
{
	isdn_ctrl ic;

	ic.driver = cs->myid;
	ic.command = ISDN_STAT_RUN;
	cs->iif.features |= addfeatures;
	cs->iif.statcallb(&ic);
	return 0;
}