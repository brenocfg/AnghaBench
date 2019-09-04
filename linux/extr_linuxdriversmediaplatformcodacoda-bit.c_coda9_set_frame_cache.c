#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u32 ;
struct coda_ctx {scalar_t__ tiled_map_type; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CODA9_CACHE_CB_BUFFER_SIZE_OFFSET ; 
 int CODA9_CACHE_CR_BUFFER_SIZE_OFFSET ; 
 int CODA9_CACHE_LUMA_BUFFER_SIZE_OFFSET ; 
 int CODA9_CACHE_PAGEMERGE_OFFSET ; 
 int /*<<< orphan*/  CODA9_CMD_SET_FRAME_CACHE_CONFIG ; 
 int /*<<< orphan*/  CODA9_CMD_SET_FRAME_CACHE_SIZE ; 
 scalar_t__ GDI_LINEAR_FRAME_MAP ; 
 scalar_t__ V4L2_PIX_FMT_NV12 ; 
 scalar_t__ V4L2_PIX_FMT_YUYV ; 
 int /*<<< orphan*/  coda_write (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void coda9_set_frame_cache(struct coda_ctx *ctx, u32 fourcc)
{
	u32 cache_size, cache_config;

	if (ctx->tiled_map_type == GDI_LINEAR_FRAME_MAP) {
		/* Luma 2x0 page, 2x6 cache, chroma 2x0 page, 2x4 cache size */
		cache_size = 0x20262024;
		cache_config = 2 << CODA9_CACHE_PAGEMERGE_OFFSET;
	} else {
		/* Luma 0x2 page, 4x4 cache, chroma 0x2 page, 4x3 cache size */
		cache_size = 0x02440243;
		cache_config = 1 << CODA9_CACHE_PAGEMERGE_OFFSET;
	}
	coda_write(ctx->dev, cache_size, CODA9_CMD_SET_FRAME_CACHE_SIZE);
	if (fourcc == V4L2_PIX_FMT_NV12 || fourcc == V4L2_PIX_FMT_YUYV) {
		cache_config |= 32 << CODA9_CACHE_LUMA_BUFFER_SIZE_OFFSET |
				16 << CODA9_CACHE_CR_BUFFER_SIZE_OFFSET |
				0 << CODA9_CACHE_CB_BUFFER_SIZE_OFFSET;
	} else {
		cache_config |= 32 << CODA9_CACHE_LUMA_BUFFER_SIZE_OFFSET |
				8 << CODA9_CACHE_CR_BUFFER_SIZE_OFFSET |
				8 << CODA9_CACHE_CB_BUFFER_SIZE_OFFSET;
	}
	coda_write(ctx->dev, cache_config, CODA9_CMD_SET_FRAME_CACHE_CONFIG);
}