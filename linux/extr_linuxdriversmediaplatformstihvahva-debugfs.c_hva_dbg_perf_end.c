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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct TYPE_4__ {scalar_t__ timestamp; } ;
struct TYPE_3__ {int /*<<< orphan*/  sequence; TYPE_2__ vb2_buf; } ;
struct hva_stream {TYPE_1__ vbuf; } ;
struct hva_ctx_dbg {int is_valid_period; int /*<<< orphan*/  window_stream_size; int /*<<< orphan*/  total_stream_size; int /*<<< orphan*/  cnt_duration; int /*<<< orphan*/  total_duration; int /*<<< orphan*/  max_duration; int /*<<< orphan*/  min_duration; int /*<<< orphan*/  begin; } ;
struct hva_ctx {int /*<<< orphan*/  name; struct hva_ctx_dbg dbg; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 struct device* ctx_to_dev (struct hva_ctx*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  do_div (scalar_t__,int) ; 
 int /*<<< orphan*/  ktime_get () ; 
 scalar_t__ ktime_us_delta (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ vb2_get_plane_payload (TYPE_2__*,int /*<<< orphan*/ ) ; 

void hva_dbg_perf_end(struct hva_ctx *ctx, struct hva_stream *stream)
{
	struct device *dev = ctx_to_dev(ctx);
	u64 div;
	u32 duration;
	u32 bytesused;
	u32 timestamp;
	struct hva_ctx_dbg *dbg = &ctx->dbg;
	ktime_t end = ktime_get();

	/* stream bytesused and timestamp in us */
	bytesused = vb2_get_plane_payload(&stream->vbuf.vb2_buf, 0);
	div = stream->vbuf.vb2_buf.timestamp;
	do_div(div, 1000);
	timestamp = (u32)div;

	/* encoding duration */
	div = (u64)ktime_us_delta(end, dbg->begin);

	dev_dbg(dev,
		"%s perf stream[%d] dts=%d encoded using %d bytes in %d us",
		ctx->name,
		stream->vbuf.sequence,
		timestamp,
		bytesused, (u32)div);

	do_div(div, 100);
	duration = (u32)div;

	dbg->min_duration = min(duration, dbg->min_duration);
	dbg->max_duration = max(duration, dbg->max_duration);
	dbg->total_duration += duration;
	dbg->cnt_duration++;

	/*
	 * the average bitrate is based on the total stream size
	 * and the total encoding periods
	 */
	dbg->total_stream_size += bytesused;
	dbg->window_stream_size += bytesused;

	dbg->is_valid_period = true;
}