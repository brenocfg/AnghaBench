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
typedef  int u32 ;
typedef  int /*<<< orphan*/  s16 ;

/* Variables and functions */
 scalar_t__ int_goertzel (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  int_sqrt (int) ; 

__attribute__((used)) static u32 noise_magnitude(s16 x[], u32 N, u32 freq_start, u32 freq_end)
{
	int i;
	u32 sum = 0;
	u32 freq_step;
	int samples = 5;

	if (N > 192) {
		/* The last 192 samples are enough for noise detection */
		x += (N - 192);
		N = 192;
	}

	freq_step = (freq_end - freq_start) / (samples - 1);

	for (i = 0; i < samples; i++) {
		sum += int_goertzel(x, N, freq_start);
		freq_start += freq_step;
	}

	return (u32)int_sqrt(sum / samples);
}