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
struct TYPE_3__ {int /*<<< orphan*/  dma; int /*<<< orphan*/  cpu; int /*<<< orphan*/  size; } ;
struct TYPE_4__ {int /*<<< orphan*/  dma; int /*<<< orphan*/  cpu; int /*<<< orphan*/  size; } ;
struct hantro_vp8_dec_hw_ctx {TYPE_1__ prob_tbl; TYPE_2__ segment_map; } ;
struct hantro_dev {int /*<<< orphan*/  dev; } ;
struct hantro_ctx {struct hantro_dev* dev; struct hantro_vp8_dec_hw_ctx vp8_dec; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void hantro_vp8_dec_exit(struct hantro_ctx *ctx)
{
	struct hantro_vp8_dec_hw_ctx *vp8_dec = &ctx->vp8_dec;
	struct hantro_dev *vpu = ctx->dev;

	dma_free_coherent(vpu->dev, vp8_dec->segment_map.size,
			  vp8_dec->segment_map.cpu, vp8_dec->segment_map.dma);
	dma_free_coherent(vpu->dev, vp8_dec->prob_tbl.size,
			  vp8_dec->prob_tbl.cpu, vp8_dec->prob_tbl.dma);
}