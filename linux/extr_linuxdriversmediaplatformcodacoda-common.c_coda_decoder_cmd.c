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
struct v4l2_decoder_cmd {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  m2m_ctx; } ;
struct coda_ctx {scalar_t__ inst_type; int hold; TYPE_1__ fh; } ;

/* Variables and functions */
 scalar_t__ CODA_INST_DECODER ; 
 int /*<<< orphan*/  coda_bit_stream_end_flag (struct coda_ctx*) ; 
 int coda_try_decoder_cmd (struct file*,void*,struct v4l2_decoder_cmd*) ; 
 struct coda_ctx* fh_to_ctx (void*) ; 
 int /*<<< orphan*/  v4l2_m2m_try_schedule (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int coda_decoder_cmd(struct file *file, void *fh,
			    struct v4l2_decoder_cmd *dc)
{
	struct coda_ctx *ctx = fh_to_ctx(fh);
	int ret;

	ret = coda_try_decoder_cmd(file, fh, dc);
	if (ret < 0)
		return ret;

	/* Ignore decoder stop command silently in encoder context */
	if (ctx->inst_type != CODA_INST_DECODER)
		return 0;

	/* Set the stream-end flag on this context */
	coda_bit_stream_end_flag(ctx);
	ctx->hold = false;
	v4l2_m2m_try_schedule(ctx->fh.m2m_ctx);

	return 0;
}