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
typedef  union audio_sample_rates {int dummy; } audio_sample_rates ;
typedef  int /*<<< orphan*/  uint32_t ;
struct audio_crtc_info {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void check_audio_bandwidth_dpmst(
	const struct audio_crtc_info *crtc_info,
	uint32_t channel_count,
	union audio_sample_rates *sample_rates)
{
	/* do nothing  */
}