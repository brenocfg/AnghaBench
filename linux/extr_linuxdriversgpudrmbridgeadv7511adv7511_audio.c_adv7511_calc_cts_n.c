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

/* Variables and functions */

__attribute__((used)) static void adv7511_calc_cts_n(unsigned int f_tmds, unsigned int fs,
			       unsigned int *cts, unsigned int *n)
{
	switch (fs) {
	case 32000:
		*n = 4096;
		break;
	case 44100:
		*n = 6272;
		break;
	case 48000:
		*n = 6144;
		break;
	}

	*cts = ((f_tmds * *n) / (128 * fs)) * 1000;
}