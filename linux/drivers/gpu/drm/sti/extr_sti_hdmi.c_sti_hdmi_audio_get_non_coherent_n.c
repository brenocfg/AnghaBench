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

__attribute__((used)) static int sti_hdmi_audio_get_non_coherent_n(unsigned int audio_fs)
{
	unsigned int n;

	switch (audio_fs) {
	case 32000:
		n = 4096;
		break;
	case 44100:
		n = 6272;
		break;
	case 48000:
		n = 6144;
		break;
	case 88200:
		n = 6272 * 2;
		break;
	case 96000:
		n = 6144 * 2;
		break;
	case 176400:
		n = 6272 * 4;
		break;
	case 192000:
		n = 6144 * 4;
		break;
	default:
		/* Not pre-defined, recommended value: 128 * fs / 1000 */
		n = (audio_fs * 128) / 1000;
	}

	return n;
}