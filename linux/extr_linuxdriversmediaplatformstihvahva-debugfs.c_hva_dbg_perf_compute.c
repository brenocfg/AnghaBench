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
typedef  int u64 ;
typedef  void* u32 ;
struct hva_ctx_dbg {scalar_t__ cnt_duration; scalar_t__ total_duration; scalar_t__ cnt_period; scalar_t__ total_period; void* avg_bitrate; scalar_t__ total_stream_size; void* avg_fps; void* avg_period; void* max_fps; void* avg_duration; } ;
struct hva_ctx {struct hva_ctx_dbg dbg; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_div (int,scalar_t__) ; 

__attribute__((used)) static void hva_dbg_perf_compute(struct hva_ctx *ctx)
{
	u64 div;
	struct hva_ctx_dbg *dbg = &ctx->dbg;

	if (dbg->cnt_duration > 0) {
		div = (u64)dbg->total_duration;
		do_div(div, dbg->cnt_duration);
		dbg->avg_duration = (u32)div;
	} else {
		dbg->avg_duration = 0;
	}

	if (dbg->total_duration > 0) {
		div = (u64)dbg->cnt_duration * 100000;
		do_div(div, dbg->total_duration);
		dbg->max_fps = (u32)div;
	} else {
		dbg->max_fps = 0;
	}

	if (dbg->cnt_period > 0) {
		div = (u64)dbg->total_period;
		do_div(div, dbg->cnt_period);
		dbg->avg_period = (u32)div;
	} else {
		dbg->avg_period = 0;
	}

	if (dbg->total_period > 0) {
		div = (u64)dbg->cnt_period * 100000;
		do_div(div, dbg->total_period);
		dbg->avg_fps = (u32)div;
	} else {
		dbg->avg_fps = 0;
	}

	if (dbg->total_period > 0) {
		/*
		 * bitrate in kbps = (video size * 8 / 1000) /
		 *                   (video duration / 10000)
		 *                 = video size * 80 / video duration
		 */
		div = (u64)dbg->total_stream_size * 80;
		do_div(div, dbg->total_period);
		dbg->avg_bitrate = (u32)div;
	} else {
		dbg->avg_bitrate = 0;
	}
}