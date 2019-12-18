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
struct TYPE_2__ {int* len; size_t* data; } ;

/* Variables and functions */
 size_t* dsp_audio_alaw_to_ulaw ; 
 TYPE_1__* samples ; 

void
dsp_audio_generate_ulaw_samples(void)
{
	int i, j;

	i = 0;
	while (samples[i].len) {
		j = 0;
		while (j < (*samples[i].len)) {
			samples[i].data[j] =
				dsp_audio_alaw_to_ulaw[samples[i].data[j]];
			j++;
		}
		i++;
	}
}