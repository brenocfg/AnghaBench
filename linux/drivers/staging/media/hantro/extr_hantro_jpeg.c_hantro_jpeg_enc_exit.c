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
struct TYPE_5__ {int /*<<< orphan*/  dma; int /*<<< orphan*/  cpu; int /*<<< orphan*/  size; } ;
struct TYPE_6__ {TYPE_2__ bounce_buffer; } ;
struct hantro_ctx {TYPE_3__ jpeg_enc; TYPE_1__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_ATTR_ALLOC_SINGLE_PAGES ; 
 int /*<<< orphan*/  dma_free_attrs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void hantro_jpeg_enc_exit(struct hantro_ctx *ctx)
{
	dma_free_attrs(ctx->dev->dev,
		       ctx->jpeg_enc.bounce_buffer.size,
		       ctx->jpeg_enc.bounce_buffer.cpu,
		       ctx->jpeg_enc.bounce_buffer.dma,
		       DMA_ATTR_ALLOC_SINGLE_PAGES);
}