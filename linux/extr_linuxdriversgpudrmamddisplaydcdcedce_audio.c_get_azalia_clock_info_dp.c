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
struct azalia_clock_info {int audio_dto_phase; int audio_dto_module; } ;
struct audio_pll_info {int dp_dto_source_clock_in_khz; } ;

/* Variables and functions */

__attribute__((used)) static void get_azalia_clock_info_dp(
	uint32_t requested_pixel_clock_in_khz,
	const struct audio_pll_info *pll_info,
	struct azalia_clock_info *azalia_clock_info)
{
	/* Reported dpDtoSourceClockInkhz value for
	 * DCE8 already adjusted for SS, do not need any
	 * adjustment here anymore
	 */

	/*audio_dto_phase = 24 * 10,000;
	 * 24MHz in [100Hz] units */
	azalia_clock_info->audio_dto_phase = 24 * 10000;

	/*audio_dto_module = dpDtoSourceClockInkhz * 10,000;
	 *  [khz] ->[100Hz] */
	azalia_clock_info->audio_dto_module =
		pll_info->dp_dto_source_clock_in_khz * 10;
}