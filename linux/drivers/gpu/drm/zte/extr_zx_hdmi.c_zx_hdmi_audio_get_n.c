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

__attribute__((used)) static inline int zx_hdmi_audio_get_n(unsigned int fs)
{
	unsigned int n;

	if (fs && (fs % 44100) == 0)
		n = 6272 * (fs / 44100);
	else
		n = fs * 128 / 1000;

	return n;
}