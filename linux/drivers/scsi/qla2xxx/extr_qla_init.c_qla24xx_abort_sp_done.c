#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  comp; } ;
struct TYPE_9__ {TYPE_2__ abt; } ;
struct srb_iocb {TYPE_3__ u; int /*<<< orphan*/  timer; } ;
struct TYPE_7__ {struct srb_iocb iocb_cmd; } ;
struct TYPE_10__ {int flags; int /*<<< orphan*/  (* free ) (TYPE_4__*) ;TYPE_1__ u; } ;
typedef  TYPE_4__ srb_t ;

/* Variables and functions */
 int SRB_WAKEUP_ON_COMP ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 

__attribute__((used)) static void qla24xx_abort_sp_done(srb_t *sp, int res)
{
	struct srb_iocb *abt = &sp->u.iocb_cmd;

	del_timer(&sp->u.iocb_cmd.timer);
	if (sp->flags & SRB_WAKEUP_ON_COMP)
		complete(&abt->u.abt.comp);
	else
		sp->free(sp);
}