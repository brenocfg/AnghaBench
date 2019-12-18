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
struct TYPE_3__ {struct hubp* hubp; } ;
struct pipe_ctx {TYPE_1__ plane_res; } ;
struct hubp {TYPE_2__* funcs; } ;
struct TYPE_4__ {int (* dmdata_status_done ) (struct hubp*) ;} ;

/* Variables and functions */
 int stub1 (struct hubp*) ; 

bool dcn20_dmdata_status_done(struct pipe_ctx *pipe_ctx)
{
	struct hubp *hubp = pipe_ctx->plane_res.hubp;

	if (!hubp)
		return false;
	return hubp->funcs->dmdata_status_done(hubp);
}