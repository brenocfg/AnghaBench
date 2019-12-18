#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int jpeg_quality; scalar_t__* jpeg_qmat_tab; } ;
struct coda_ctx {TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  chroma_q ; 
 int /*<<< orphan*/  coda_scale_quant_table (scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  luma_q ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,int) ; 

void coda_set_jpeg_compression_quality(struct coda_ctx *ctx, int quality)
{
	unsigned int scale;

	ctx->params.jpeg_quality = quality;

	/* Clip quality setting to [5,100] interval */
	if (quality > 100)
		quality = 100;
	if (quality < 5)
		quality = 5;

	/*
	 * Non-linear scaling factor:
	 * [5,50] -> [1000..100], [51,100] -> [98..0]
	 */
	if (quality < 50)
		scale = 5000 / quality;
	else
		scale = 200 - 2 * quality;

	if (ctx->params.jpeg_qmat_tab[0]) {
		memcpy(ctx->params.jpeg_qmat_tab[0], luma_q, 64);
		coda_scale_quant_table(ctx->params.jpeg_qmat_tab[0], scale);
	}
	if (ctx->params.jpeg_qmat_tab[1]) {
		memcpy(ctx->params.jpeg_qmat_tab[1], chroma_q, 64);
		coda_scale_quant_table(ctx->params.jpeg_qmat_tab[1], scale);
	}
}