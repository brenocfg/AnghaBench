#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  fxiocb_comp; } ;
struct TYPE_11__ {TYPE_2__ fxiocb; } ;
struct TYPE_15__ {scalar_t__ expires; } ;
struct TYPE_13__ {TYPE_3__ u; TYPE_7__ timer; } ;
struct TYPE_12__ {TYPE_5__ iocb_cmd; } ;
struct TYPE_14__ {scalar_t__ type; int start_timer; TYPE_4__ u; TYPE_1__* vha; int /*<<< orphan*/  free; } ;
typedef  TYPE_6__ srb_t ;
struct TYPE_9__ {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 unsigned long HZ ; 
 scalar_t__ IS_QLAFX00 (int /*<<< orphan*/ ) ; 
 scalar_t__ SRB_FXIOCB_DCMD ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  qla2x00_sp_free ; 
 int /*<<< orphan*/  qla2x00_sp_timeout ; 
 int /*<<< orphan*/  timer_setup (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void qla2x00_init_timer(srb_t *sp, unsigned long tmo)
{
	timer_setup(&sp->u.iocb_cmd.timer, qla2x00_sp_timeout, 0);
	sp->u.iocb_cmd.timer.expires = jiffies + tmo * HZ;
	sp->free = qla2x00_sp_free;
	if (IS_QLAFX00(sp->vha->hw) && sp->type == SRB_FXIOCB_DCMD)
		init_completion(&sp->u.iocb_cmd.u.fxiocb.fxiocb_comp);
	sp->start_timer = 1;
}