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
struct s5p_jpeg_ctx {scalar_t__ mode; scalar_t__ state; int hdr_parsed; } ;

/* Variables and functions */
 scalar_t__ JPEGCTX_RESOLUTION_CHANGE ; 
 scalar_t__ S5P_JPEG_DECODE ; 

__attribute__((used)) static int s5p_jpeg_job_ready(void *priv)
{
	struct s5p_jpeg_ctx *ctx = priv;

	if (ctx->mode == S5P_JPEG_DECODE) {
		/*
		 * We have only one input buffer and one output buffer. If there
		 * is a resolution change event, no need to continue decoding.
		 */
		if (ctx->state == JPEGCTX_RESOLUTION_CHANGE)
			return 0;

		return ctx->hdr_parsed;
	}

	return 1;
}