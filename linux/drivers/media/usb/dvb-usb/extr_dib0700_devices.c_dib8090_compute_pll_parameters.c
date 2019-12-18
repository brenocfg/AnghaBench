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
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_2__ {int frequency; } ;
struct dvb_frontend {TYPE_1__ dtv_property_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  deb_info (char*,int,...) ; 

__attribute__((used)) static u8 dib8090_compute_pll_parameters(struct dvb_frontend *fe)
{
	u8 optimal_pll_ratio = 20;
	u32 freq_adc, ratio, rest, max = 0;
	u8 pll_ratio;

	for (pll_ratio = 17; pll_ratio <= 20; pll_ratio++) {
		freq_adc = 12 * pll_ratio * (1 << 8) / 16;
		ratio = ((fe->dtv_property_cache.frequency / 1000) * (1 << 8) / 1000) / freq_adc;
		rest = ((fe->dtv_property_cache.frequency / 1000) * (1 << 8) / 1000) - ratio * freq_adc;

		if (rest > freq_adc / 2)
			rest = freq_adc - rest;
		deb_info("PLL ratio=%i rest=%i\n", pll_ratio, rest);
		if ((rest > max) && (rest > 717)) {
			optimal_pll_ratio = pll_ratio;
			max = rest;
		}
	}
	deb_info("optimal PLL ratio=%i\n", optimal_pll_ratio);

	return optimal_pll_ratio;
}