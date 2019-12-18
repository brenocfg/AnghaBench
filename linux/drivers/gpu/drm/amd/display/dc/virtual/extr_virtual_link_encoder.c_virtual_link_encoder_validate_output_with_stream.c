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
struct link_encoder {int dummy; } ;
struct dc_stream_state {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static bool virtual_link_encoder_validate_output_with_stream(
	struct link_encoder *enc,
	const struct dc_stream_state *stream) { return true; }