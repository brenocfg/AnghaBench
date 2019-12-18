#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_3__* tile; } ;
struct TYPE_6__ {unsigned int num_cols; TYPE_1__* tile; } ;
struct ipu_image_convert_ctx {int next_tile; scalar_t__* resize_coeffs_h; scalar_t__* resize_coeffs_v; TYPE_4__ out; TYPE_2__ in; } ;
struct TYPE_7__ {scalar_t__ width; scalar_t__ height; } ;
struct TYPE_5__ {scalar_t__ width; scalar_t__ height; } ;

/* Variables and functions */

__attribute__((used)) static bool ic_settings_changed(struct ipu_image_convert_ctx *ctx)
{
	unsigned int cur_tile = ctx->next_tile - 1;
	unsigned int next_tile = ctx->next_tile;

	if (ctx->resize_coeffs_h[cur_tile % ctx->in.num_cols] !=
	    ctx->resize_coeffs_h[next_tile % ctx->in.num_cols] ||
	    ctx->resize_coeffs_v[cur_tile / ctx->in.num_cols] !=
	    ctx->resize_coeffs_v[next_tile / ctx->in.num_cols] ||
	    ctx->in.tile[cur_tile].width != ctx->in.tile[next_tile].width ||
	    ctx->in.tile[cur_tile].height != ctx->in.tile[next_tile].height ||
	    ctx->out.tile[cur_tile].width != ctx->out.tile[next_tile].width ||
	    ctx->out.tile[cur_tile].height != ctx->out.tile[next_tile].height)
		return true;

	return false;
}