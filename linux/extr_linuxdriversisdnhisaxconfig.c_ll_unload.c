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
struct TYPE_4__ {int /*<<< orphan*/  (* statcallb ) (TYPE_2__*) ;} ;
struct IsdnCardState {int /*<<< orphan*/ * dlog; int /*<<< orphan*/ * status_end; int /*<<< orphan*/ * status_write; int /*<<< orphan*/ * status_read; int /*<<< orphan*/ * status_buf; TYPE_1__ iif; int /*<<< orphan*/  myid; } ;
struct TYPE_5__ {int /*<<< orphan*/  driver; int /*<<< orphan*/  command; } ;
typedef  TYPE_2__ isdn_ctrl ;

/* Variables and functions */
 int /*<<< orphan*/  ISDN_STAT_UNLOAD ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static void ll_unload(struct IsdnCardState *cs)
{
	isdn_ctrl ic;

	ic.command = ISDN_STAT_UNLOAD;
	ic.driver = cs->myid;
	cs->iif.statcallb(&ic);
	kfree(cs->status_buf);
	cs->status_read = NULL;
	cs->status_write = NULL;
	cs->status_end = NULL;
	kfree(cs->dlog);
	cs->dlog = NULL;
}