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
typedef  int s32 ;

/* Variables and functions */
 int* dsp_audio_law_to_s32 ; 
 int /*<<< orphan*/ * dsp_audio_mix_law ; 
 int /*<<< orphan*/ * dsp_audio_s16_to_law ; 

void
dsp_audio_generate_mix_table(void)
{
	int i, j;
	s32 sample;

	i = 0;
	while (i < 256) {
		j = 0;
		while (j < 256) {
			sample = dsp_audio_law_to_s32[i];
			sample += dsp_audio_law_to_s32[j];
			if (sample > 32767)
				sample = 32767;
			if (sample < -32768)
				sample = -32768;
			dsp_audio_mix_law[(i << 8) | j] =
				dsp_audio_s16_to_law[sample & 0xffff];
			j++;
		}
		i++;
	}
}