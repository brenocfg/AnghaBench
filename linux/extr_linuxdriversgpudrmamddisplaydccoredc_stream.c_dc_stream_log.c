#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  display_color_depth; int /*<<< orphan*/  pixel_encoding; int /*<<< orphan*/  v_total; int /*<<< orphan*/  h_total; int /*<<< orphan*/  pix_clk_khz; } ;
struct TYPE_8__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_7__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct dc_stream_state {TYPE_6__* sink; TYPE_3__ timing; int /*<<< orphan*/  output_color_space; TYPE_2__ dst; TYPE_1__ src; } ;
struct dc {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  serial_number; int /*<<< orphan*/  display_name; } ;
struct TYPE_12__ {TYPE_5__* link; TYPE_4__ edid_caps; } ;
struct TYPE_11__ {int /*<<< orphan*/  link_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_LOG_DC (char*,struct dc_stream_state const*,...) ; 

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
			stream->timing.pix_clk_khz,
			stream->timing.h_total,
			stream->timing.v_total,
			stream->timing.pixel_encoding,
			stream->timing.display_color_depth);
	DC_LOG_DC(
			"\tsink name: %s, serial: %d\n",
			stream->sink->edid_caps.display_name,
			stream->sink->edid_caps.serial_number);
	DC_LOG_DC(
			"\tlink: %d\n",
			stream->sink->link->link_index);
}