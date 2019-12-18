#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  (* free ) (TYPE_1__*) ;TYPE_3__* fcport; } ;
typedef  TYPE_1__ srb_t ;
struct TYPE_6__ {int flags; int /*<<< orphan*/  login_gen; } ;

/* Variables and functions */
 int FCF_ASYNC_ACTIVE ; 
 int FCF_ASYNC_SENT ; 
 int /*<<< orphan*/  qlt_logo_completion_handler (TYPE_3__*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static void qla2x00_async_logout_sp_done(srb_t *sp, int res)
{
	sp->fcport->flags &= ~(FCF_ASYNC_SENT | FCF_ASYNC_ACTIVE);
	sp->fcport->login_gen++;
	qlt_logo_completion_handler(sp->fcport, res);
	sp->free(sp);
}