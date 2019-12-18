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
struct TYPE_3__ {unsigned int mv_col_buf_dma; unsigned int mv_col_buf_field_size; } ;
struct TYPE_4__ {TYPE_1__ h264; } ;
struct cedrus_ctx {TYPE_2__ codec; } ;
typedef  unsigned int dma_addr_t ;

/* Variables and functions */

__attribute__((used)) static dma_addr_t cedrus_h264_mv_col_buf_addr(struct cedrus_ctx *ctx,
					      unsigned int position,
					      unsigned int field)
{
	dma_addr_t addr = ctx->codec.h264.mv_col_buf_dma;

	/* Adjust for the position */
	addr += position * ctx->codec.h264.mv_col_buf_field_size * 2;

	/* Adjust for the field */
	addr += field * ctx->codec.h264.mv_col_buf_field_size;

	return addr;
}