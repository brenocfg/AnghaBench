#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_6__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_7__ {TYPE_1__ crop; } ;
struct TYPE_10__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_9__ {TYPE_5__ crop; } ;
struct bdisp_ctx {TYPE_3__* bdisp_dev; TYPE_2__ dst; TYPE_4__ src; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ bdisp_hw_get_inc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bdisp_hw_get_hv_inc(struct bdisp_ctx *ctx, u16 *h_inc, u16 *v_inc)
{
	u32 src_w, src_h, dst_w, dst_h;

	src_w = ctx->src.crop.width;
	src_h = ctx->src.crop.height;
	dst_w = ctx->dst.crop.width;
	dst_h = ctx->dst.crop.height;

	if (bdisp_hw_get_inc(src_w, dst_w, h_inc) ||
	    bdisp_hw_get_inc(src_h, dst_h, v_inc)) {
		dev_err(ctx->bdisp_dev->dev,
			"scale factors failed (%dx%d)->(%dx%d)\n",
			src_w, src_h, dst_w, dst_h);
		return -EINVAL;
	}

	return 0;
}