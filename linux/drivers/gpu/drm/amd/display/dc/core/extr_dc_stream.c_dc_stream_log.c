#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int pix_clk_100hz; int /*<<< orphan*/  display_color_depth; int /*<<< orphan*/  pixel_encoding; int /*<<< orphan*/  v_total; int /*<<< orphan*/  h_total; } ;
struct TYPE_6__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_5__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct dc_stream_state {TYPE_4__* link; TYPE_3__ timing; int /*<<< orphan*/  output_color_space; TYPE_2__ dst; TYPE_1__ src; } ;
struct dc {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  link_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_LOG_DC (char*,...) ; 

void dc_stream_log(const struct dc *dc, const struct dc_stream_state *stream)
{
	DC_LOG_DC(
			"core_stream 0x%p: src: %d, %d, %d, %d; dst: %d, %d, %d, %d, colorSpace:%d\n",
			stream,
			stream->src.x,
			stream->src.y,
			stream->src.width,
			stream->src.height,
			stream->dst.x,
			stream->dst.y,
			stream->dst.width,
			stream->dst.height,
			stream->output_color_space);
	DC_LOG_DC(
			"\tpix_clk_khz: %d, h_total: %d, v_total: %d, pixelencoder:%d, displaycolorDepth:%d\n",
			stream->timing.pix_clk_100hz / 10,
			stream->timing.h_total,
			stream->timing.v_total,
			stream->timing.pixel_encoding,
			stream->timing.display_color_depth);
	DC_LOG_DC(
			"\tlink: %d\n",
			stream->link->link_index);
}