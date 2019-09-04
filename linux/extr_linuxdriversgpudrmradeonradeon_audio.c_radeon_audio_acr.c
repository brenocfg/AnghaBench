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
typedef  size_t u8 ;
typedef  struct radeon_hdmi_acr {int member_0; int member_1; int member_2; int member_3; int member_4; int member_5; int member_6; unsigned int clock; int /*<<< orphan*/  n_48khz; int /*<<< orphan*/  cts_48khz; int /*<<< orphan*/  n_44_1khz; int /*<<< orphan*/  cts_44_1khz; int /*<<< orphan*/  n_32khz; int /*<<< orphan*/  cts_32khz; } const radeon_hdmi_acr ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct radeon_hdmi_acr const*) ; 
 int /*<<< orphan*/  radeon_audio_calc_cts (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static const struct radeon_hdmi_acr* radeon_audio_acr(unsigned int clock)
{
	static struct radeon_hdmi_acr res;
	u8 i;

	static const struct radeon_hdmi_acr hdmi_predefined_acr[] = {
		/*       32kHz    44.1kHz   48kHz    */
		/* Clock      N     CTS      N     CTS      N     CTS */
		{  25175,  4096,  25175, 28224, 125875,  6144,  25175 }, /*  25,20/1.001 MHz */
		{  25200,  4096,  25200,  6272,  28000,  6144,  25200 }, /*  25.20       MHz */
		{  27000,  4096,  27000,  6272,  30000,  6144,  27000 }, /*  27.00       MHz */
		{  27027,  4096,  27027,  6272,  30030,  6144,  27027 }, /*  27.00*1.001 MHz */
		{  54000,  4096,  54000,  6272,  60000,  6144,  54000 }, /*  54.00       MHz */
		{  54054,  4096,  54054,  6272,  60060,  6144,  54054 }, /*  54.00*1.001 MHz */
		{  74176,  4096,  74176,  5733,  75335,  6144,  74176 }, /*  74.25/1.001 MHz */
		{  74250,  4096,  74250,  6272,  82500,  6144,  74250 }, /*  74.25       MHz */
		{ 148352,  4096, 148352,  5733, 150670,  6144, 148352 }, /* 148.50/1.001 MHz */
		{ 148500,  4096, 148500,  6272, 165000,  6144, 148500 }, /* 148.50       MHz */
	};

	/* Precalculated values for common clocks */
	for (i = 0; i < ARRAY_SIZE(hdmi_predefined_acr); i++)
		if (hdmi_predefined_acr[i].clock == clock)
			return &hdmi_predefined_acr[i];

	/* And odd clocks get manually calculated */
	radeon_audio_calc_cts(clock, &res.cts_32khz, &res.n_32khz, 32000);
	radeon_audio_calc_cts(clock, &res.cts_44_1khz, &res.n_44_1khz, 44100);
	radeon_audio_calc_cts(clock, &res.cts_48khz, &res.n_48khz, 48000);

	return &res;
}