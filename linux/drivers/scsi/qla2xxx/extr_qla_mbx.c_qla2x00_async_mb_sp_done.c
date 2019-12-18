#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int rc; int /*<<< orphan*/  comp; } ;
struct TYPE_8__ {TYPE_1__ mbx; } ;
struct TYPE_9__ {TYPE_2__ u; } ;
struct TYPE_10__ {TYPE_3__ iocb_cmd; } ;
struct TYPE_11__ {TYPE_4__ u; } ;
typedef  TYPE_5__ srb_t ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qla2x00_async_mb_sp_done(srb_t *sp, int res)
{
	sp->u.iocb_cmd.u.mbx.rc = res;

	complete(&sp->u.iocb_cmd.u.mbx.comp);
	/* don't free sp here. Let the caller do the free */
}