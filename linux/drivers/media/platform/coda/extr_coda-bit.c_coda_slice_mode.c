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
typedef  int u32 ;
struct TYPE_2__ {int slice_mode; int slice_max_mb; int slice_max_bits; } ;
struct coda_ctx {TYPE_1__ params; } ;

/* Variables and functions */
 int CODA_SLICING_MODE_MASK ; 
 int CODA_SLICING_MODE_OFFSET ; 
 int CODA_SLICING_SIZE_MASK ; 
 int CODA_SLICING_SIZE_OFFSET ; 
 int CODA_SLICING_UNIT_MASK ; 
 int CODA_SLICING_UNIT_OFFSET ; 
#define  V4L2_MPEG_VIDEO_MULTI_SLICE_MODE_MAX_BYTES 130 
#define  V4L2_MPEG_VIDEO_MULTI_SLICE_MODE_MAX_MB 129 
#define  V4L2_MPEG_VIDEO_MULTI_SLICE_MODE_SINGLE 128 

__attribute__((used)) static u32 coda_slice_mode(struct coda_ctx *ctx)
{
	int size, unit;

	switch (ctx->params.slice_mode) {
	case V4L2_MPEG_VIDEO_MULTI_SLICE_MODE_SINGLE:
	default:
		return 0;
	case V4L2_MPEG_VIDEO_MULTI_SLICE_MODE_MAX_MB:
		size = ctx->params.slice_max_mb;
		unit = 1;
		break;
	case V4L2_MPEG_VIDEO_MULTI_SLICE_MODE_MAX_BYTES:
		size = ctx->params.slice_max_bits;
		unit = 0;
		break;
	}

	return ((size & CODA_SLICING_SIZE_MASK) << CODA_SLICING_SIZE_OFFSET) |
	       ((unit & CODA_SLICING_UNIT_MASK) << CODA_SLICING_UNIT_OFFSET) |
	       ((1 & CODA_SLICING_MODE_MASK) << CODA_SLICING_MODE_OFFSET);
}