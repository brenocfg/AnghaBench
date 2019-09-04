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
struct TYPE_6__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct mtk_mdp_frame {int /*<<< orphan*/  height; int /*<<< orphan*/  width; TYPE_3__ crop; } ;
struct TYPE_5__ {TYPE_1__* vsi; } ;
struct mtk_mdp_ctx {TYPE_2__ vpu; struct mtk_mdp_frame s_frame; } ;
struct mdp_config {int /*<<< orphan*/  h; int /*<<< orphan*/  w; scalar_t__ y; scalar_t__ x; int /*<<< orphan*/  crop_h; int /*<<< orphan*/  crop_w; int /*<<< orphan*/  crop_y; int /*<<< orphan*/  crop_x; } ;
struct TYPE_4__ {struct mdp_config src_config; } ;

/* Variables and functions */

void mtk_mdp_hw_set_in_size(struct mtk_mdp_ctx *ctx)
{
	struct mtk_mdp_frame *frame = &ctx->s_frame;
	struct mdp_config *config = &ctx->vpu.vsi->src_config;

	/* Set input pixel offset */
	config->crop_x = frame->crop.left;
	config->crop_y = frame->crop.top;

	/* Set input cropped size */
	config->crop_w = frame->crop.width;
	config->crop_h = frame->crop.height;

	/* Set input original size */
	config->x = 0;
	config->y = 0;
	config->w = frame->width;
	config->h = frame->height;
}