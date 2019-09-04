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
struct TYPE_4__ {int /*<<< orphan*/  pixel_encoding; int /*<<< orphan*/  display_color_depth; } ;
struct TYPE_3__ {int /*<<< orphan*/  pixel_encoding; int /*<<< orphan*/  c_depth; int /*<<< orphan*/  clamping_level; } ;
struct dc_stream_state {TYPE_2__ timing; TYPE_1__ clamping; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLAMPING_FULL_RANGE ; 

__attribute__((used)) static void build_clamping_params(struct dc_stream_state *stream)
{
	stream->clamping.clamping_level = CLAMPING_FULL_RANGE;
	stream->clamping.c_depth = stream->timing.display_color_depth;
	stream->clamping.pixel_encoding = stream->timing.pixel_encoding;
}