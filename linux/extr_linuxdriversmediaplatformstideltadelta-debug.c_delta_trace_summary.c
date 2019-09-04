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
struct delta_streaminfo {int dummy; } ;
struct delta_dev {int /*<<< orphan*/  dev; } ;
struct delta_ctx {int flags; int /*<<< orphan*/  decode_errors; int /*<<< orphan*/  stream_errors; int /*<<< orphan*/  dropped_frames; int /*<<< orphan*/  output_frames; int /*<<< orphan*/  decoded_frames; int /*<<< orphan*/  name; struct delta_streaminfo streaminfo; struct delta_dev* dev; } ;
typedef  int /*<<< orphan*/  str ;

/* Variables and functions */
 int DELTA_FLAG_STREAMINFO ; 
 int /*<<< orphan*/  delta_streaminfo_str (struct delta_streaminfo*,unsigned char*,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void delta_trace_summary(struct delta_ctx *ctx)
{
	struct delta_dev *delta = ctx->dev;
	struct delta_streaminfo *s = &ctx->streaminfo;
	unsigned char str[100] = "";

	if (!(ctx->flags & DELTA_FLAG_STREAMINFO))
		return;

	dev_dbg(delta->dev, "%s %s, %d frames decoded, %d frames output, %d frames dropped, %d stream errors, %d decode errors",
		ctx->name,
		delta_streaminfo_str(s, str, sizeof(str)),
		ctx->decoded_frames,
		ctx->output_frames,
		ctx->dropped_frames,
		ctx->stream_errors,
		ctx->decode_errors);
}