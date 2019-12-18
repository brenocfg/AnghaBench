#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ct_entry_24xx {int /*<<< orphan*/  handle; } ;
struct TYPE_11__ {struct ct_entry_24xx* iocb; } ;
struct TYPE_7__ {TYPE_6__ ctarg; } ;
struct TYPE_8__ {TYPE_1__ u; } ;
struct TYPE_9__ {TYPE_2__ iocb_cmd; } ;
struct TYPE_10__ {int /*<<< orphan*/  handle; TYPE_3__ u; int /*<<< orphan*/  vha; } ;
typedef  TYPE_4__ srb_t ;

/* Variables and functions */
 int /*<<< orphan*/  qla24xx_prep_ms_iocb (int /*<<< orphan*/ ,TYPE_6__*) ; 

__attribute__((used)) static void
qla2x00_ctpthru_cmd_iocb(srb_t *sp, struct ct_entry_24xx *ct_pkt)
{
	sp->u.iocb_cmd.u.ctarg.iocb = ct_pkt;
	qla24xx_prep_ms_iocb(sp->vha, &sp->u.iocb_cmd.u.ctarg);
	ct_pkt->handle = sp->handle;
}