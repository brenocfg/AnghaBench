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
struct hantro_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int size; int /*<<< orphan*/  cpu; int /*<<< orphan*/  dma; } ;
struct TYPE_4__ {TYPE_1__ qtable; } ;
struct hantro_ctx {TYPE_2__ mpeg2_dec; struct hantro_dev* dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zigzag ; 

int hantro_mpeg2_dec_init(struct hantro_ctx *ctx)
{
	struct hantro_dev *vpu = ctx->dev;

	ctx->mpeg2_dec.qtable.size = ARRAY_SIZE(zigzag) * 4;
	ctx->mpeg2_dec.qtable.cpu =
		dma_alloc_coherent(vpu->dev,
				   ctx->mpeg2_dec.qtable.size,
				   &ctx->mpeg2_dec.qtable.dma,
				   GFP_KERNEL);
	if (!ctx->mpeg2_dec.qtable.cpu)
		return -ENOMEM;
	return 0;
}