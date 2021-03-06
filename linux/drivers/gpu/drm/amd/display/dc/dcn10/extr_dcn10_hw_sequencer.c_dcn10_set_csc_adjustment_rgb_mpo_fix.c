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
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_5__ {TYPE_3__* dpp; } ;
struct pipe_ctx {TYPE_2__ plane_res; } ;
struct TYPE_6__ {TYPE_1__* funcs; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* dpp_set_csc_adjustment ) (TYPE_3__*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dcn10_set_csc_adjustment_rgb_mpo_fix(struct pipe_ctx *pipe_ctx, uint16_t *matrix)
{
	// Override rear plane RGB bias to fix MPO brightness
	uint16_t rgb_bias = matrix[3];

	matrix[3] = 0;
	matrix[7] = 0;
	matrix[11] = 0;
	pipe_ctx->plane_res.dpp->funcs->dpp_set_csc_adjustment(pipe_ctx->plane_res.dpp, matrix);
	matrix[3] = rgb_bias;
	matrix[7] = rgb_bias;
	matrix[11] = rgb_bias;
}