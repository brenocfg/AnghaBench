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
struct TYPE_2__ {int pix_clk_100hz; int /*<<< orphan*/  v_total; int /*<<< orphan*/  h_total; } ;
struct dc_stream_state {TYPE_1__ timing; } ;

/* Variables and functions */
 unsigned long long div_u64 (unsigned long long,int /*<<< orphan*/ ) ; 

unsigned long long mod_freesync_calc_nominal_field_rate(
			const struct dc_stream_state *stream)
{
	unsigned long long nominal_field_rate_in_uhz = 0;

	/* Calculate nominal field rate for stream */
	nominal_field_rate_in_uhz = stream->timing.pix_clk_100hz / 10;
	nominal_field_rate_in_uhz *= 1000ULL * 1000ULL * 1000ULL;
	nominal_field_rate_in_uhz = div_u64(nominal_field_rate_in_uhz,
						stream->timing.h_total);
	nominal_field_rate_in_uhz = div_u64(nominal_field_rate_in_uhz,
						stream->timing.v_total);

	return nominal_field_rate_in_uhz;
}