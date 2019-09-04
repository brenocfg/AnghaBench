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
struct hva_streaminfo {int /*<<< orphan*/  level; int /*<<< orphan*/  profile; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  streamformat; } ;
struct hva_frameinfo {int /*<<< orphan*/  aligned_height; int /*<<< orphan*/  aligned_width; int /*<<< orphan*/  pixelformat; } ;
struct hva_ctx {int flags; int /*<<< orphan*/  frame_errors; int /*<<< orphan*/  encode_errors; int /*<<< orphan*/  sys_errors; int /*<<< orphan*/  encoded_frames; int /*<<< orphan*/  name; struct hva_frameinfo frameinfo; struct hva_streaminfo streaminfo; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int HVA_FLAG_STREAMINFO ; 
 struct device* ctx_to_dev (struct hva_ctx*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hva_dbg_summary(struct hva_ctx *ctx)
{
	struct device *dev = ctx_to_dev(ctx);
	struct hva_streaminfo *stream = &ctx->streaminfo;
	struct hva_frameinfo *frame = &ctx->frameinfo;

	if (!(ctx->flags & HVA_FLAG_STREAMINFO))
		return;

	dev_dbg(dev, "%s %4.4s %dx%d > %4.4s %dx%d %s %s: %d frames encoded, %d system errors, %d encoding errors, %d frame errors\n",
		ctx->name,
		(char *)&frame->pixelformat,
		frame->aligned_width, frame->aligned_height,
		(char *)&stream->streamformat,
		stream->width, stream->height,
		stream->profile, stream->level,
		ctx->encoded_frames,
		ctx->sys_errors,
		ctx->encode_errors,
		ctx->frame_errors);
}