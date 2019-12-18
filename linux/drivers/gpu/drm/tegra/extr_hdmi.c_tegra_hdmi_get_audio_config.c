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
typedef  int uint64_t ;
struct tegra_hdmi_audio_config {int n; int cts; int aval; } ;
typedef  int int64_t ;

/* Variables and functions */
 int BIT (int) ; 
 int EINVAL ; 
 void* abs (int) ; 
 int /*<<< orphan*/  do_div (int,unsigned int const) ; 
 int /*<<< orphan*/  memset (struct tegra_hdmi_audio_config*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
tegra_hdmi_get_audio_config(unsigned int audio_freq, unsigned int pix_clock,
			    struct tegra_hdmi_audio_config *config)
{
	const unsigned int afreq = 128 * audio_freq;
	const unsigned int min_n = afreq / 1500;
	const unsigned int max_n = afreq / 300;
	const unsigned int ideal_n = afreq / 1000;
	int64_t min_err = (uint64_t)-1 >> 1;
	unsigned int min_delta = -1;
	int n;

	memset(config, 0, sizeof(*config));
	config->n = -1;

	for (n = min_n; n <= max_n; n++) {
		uint64_t cts_f, aval_f;
		unsigned int delta;
		int64_t cts, err;

		/* compute aval in 48.16 fixed point */
		aval_f = ((int64_t)24000000 << 16) * n;
		do_div(aval_f, afreq);
		/* It should round without any rest */
		if (aval_f & 0xFFFF)
			continue;

		/* Compute cts in 48.16 fixed point */
		cts_f = ((int64_t)pix_clock << 16) * n;
		do_div(cts_f, afreq);
		/* Round it to the nearest integer */
		cts = (cts_f & ~0xFFFF) + ((cts_f & BIT(15)) << 1);

		delta = abs(n - ideal_n);

		/* Compute the absolute error */
		err = abs((int64_t)cts_f - cts);
		if (err < min_err || (err == min_err && delta < min_delta)) {
			config->n = n;
			config->cts = cts >> 16;
			config->aval = aval_f >> 16;
			min_delta = delta;
			min_err = err;
		}
	}

	return config->n != -1 ? 0 : -EINVAL;
}