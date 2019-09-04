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
typedef  int uint32_t ;
struct azalia_clock_info {int audio_dto_phase; int audio_dto_module; } ;

/* Variables and functions */

__attribute__((used)) static void get_azalia_clock_info_hdmi(
	uint32_t crtc_pixel_clock_in_khz,
	uint32_t actual_pixel_clock_in_khz,
	struct azalia_clock_info *azalia_clock_info)
{
	/* audio_dto_phase= 24 * 10,000;
	 *   24MHz in [100Hz] units */
	azalia_clock_info->audio_dto_phase =
			24 * 10000;

	/* audio_dto_module = PCLKFrequency * 10,000;
	 *  [khz] -> [100Hz] */
	azalia_clock_info->audio_dto_module =
			actual_pixel_clock_in_khz * 10;
}