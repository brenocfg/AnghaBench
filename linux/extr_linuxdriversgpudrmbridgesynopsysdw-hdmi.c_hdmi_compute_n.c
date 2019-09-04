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

__attribute__((used)) static unsigned int hdmi_compute_n(unsigned int freq, unsigned long pixel_clk)
{
	unsigned int n = (128 * freq) / 1000;
	unsigned int mult = 1;

	while (freq > 48000) {
		mult *= 2;
		freq /= 2;
	}

	switch (freq) {
	case 32000:
		if (pixel_clk == 25175000)
			n = 4576;
		else if (pixel_clk == 27027000)
			n = 4096;
		else if (pixel_clk == 74176000 || pixel_clk == 148352000)
			n = 11648;
		else
			n = 4096;
		n *= mult;
		break;

	case 44100:
		if (pixel_clk == 25175000)
			n = 7007;
		else if (pixel_clk == 74176000)
			n = 17836;
		else if (pixel_clk == 148352000)
			n = 8918;
		else
			n = 6272;
		n *= mult;
		break;

	case 48000:
		if (pixel_clk == 25175000)
			n = 6864;
		else if (pixel_clk == 27027000)
			n = 6144;
		else if (pixel_clk == 74176000)
			n = 11648;
		else if (pixel_clk == 148352000)
			n = 5824;
		else
			n = 6144;
		n *= mult;
		break;

	default:
		break;
	}

	return n;
}