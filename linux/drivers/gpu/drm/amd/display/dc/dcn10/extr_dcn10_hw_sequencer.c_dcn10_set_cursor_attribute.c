#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_5__* dpp; TYPE_6__* hubp; } ;
struct pipe_ctx {TYPE_4__ plane_res; TYPE_1__* stream; } ;
struct dc_cursor_attributes {int dummy; } ;
struct TYPE_12__ {TYPE_2__* funcs; } ;
struct TYPE_11__ {TYPE_3__* funcs; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* set_cursor_attributes ) (TYPE_5__*,struct dc_cursor_attributes*) ;} ;
struct TYPE_8__ {int /*<<< orphan*/  (* set_cursor_attributes ) (TYPE_6__*,struct dc_cursor_attributes*) ;} ;
struct TYPE_7__ {struct dc_cursor_attributes cursor_attributes; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_6__*,struct dc_cursor_attributes*) ; 
 int /*<<< orphan*/  stub2 (TYPE_5__*,struct dc_cursor_attributes*) ; 

__attribute__((used)) static void dcn10_set_cursor_attribute(struct pipe_ctx *pipe_ctx)
{
	struct dc_cursor_attributes *attributes = &pipe_ctx->stream->cursor_attributes;

	pipe_ctx->plane_res.hubp->funcs->set_cursor_attributes(
			pipe_ctx->plane_res.hubp, attributes);
	pipe_ctx->plane_res.dpp->funcs->set_cursor_attributes(
		pipe_ctx->plane_res.dpp, attributes);
}