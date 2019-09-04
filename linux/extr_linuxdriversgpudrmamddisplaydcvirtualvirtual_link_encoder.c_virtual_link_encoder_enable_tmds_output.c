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
typedef  int /*<<< orphan*/  uint32_t ;
struct link_encoder {int dummy; } ;
typedef  enum signal_type { ____Placeholder_signal_type } signal_type ;
typedef  enum dc_color_depth { ____Placeholder_dc_color_depth } dc_color_depth ;
typedef  enum clock_source_id { ____Placeholder_clock_source_id } clock_source_id ;

/* Variables and functions */

__attribute__((used)) static void virtual_link_encoder_enable_tmds_output(
	struct link_encoder *enc,
	enum clock_source_id clock_source,
	enum dc_color_depth color_depth,
	enum signal_type signal,
	uint32_t pixel_clock) {}