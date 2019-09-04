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
struct stb0899_internal {int master_clk; int srate; } ;
struct stb0899_state {struct stb0899_config* config; struct stb0899_internal internal; } ;
struct stb0899_config {int btr_nco_bits; } ;

/* Variables and functions */
 int Log2Int (int) ; 

__attribute__((used)) static u32 stb0899_dvbs2_calc_srate(struct stb0899_state *state)
{
	struct stb0899_internal *internal	= &state->internal;
	struct stb0899_config *config		= state->config;

	u32 dec_ratio, dec_rate, decim, remain, intval, btr_nom_freq;
	u32 master_clk, srate;

	dec_ratio = (internal->master_clk * 2) / (5 * internal->srate);
	dec_ratio = (dec_ratio == 0) ? 1 : dec_ratio;
	dec_rate = Log2Int(dec_ratio);
	decim = 1 << dec_rate;
	master_clk = internal->master_clk / 1000;
	srate = internal->srate / 1000;

	if (decim <= 4) {
		intval = (decim * (1 << (config->btr_nco_bits - 1))) / master_clk;
		remain = (decim * (1 << (config->btr_nco_bits - 1))) % master_clk;
	} else {
		intval = (1 << (config->btr_nco_bits - 1)) / (master_clk / 100) * decim / 100;
		remain = (decim * (1 << (config->btr_nco_bits - 1))) % master_clk;
	}
	btr_nom_freq = (intval * srate) + ((remain * srate) / master_clk);

	return btr_nom_freq;
}