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
struct dtv_frontend_properties {scalar_t__ symbol_rate; int frequency; } ;
struct dvb_frontend {struct cx24123_state* demodulator_priv; struct dtv_frontend_properties dtv_property_cache; } ;
struct cx24123_state {int pllarg; int /*<<< orphan*/  bandselectarg; int /*<<< orphan*/  FILTune; int /*<<< orphan*/  VGAarg; int /*<<< orphan*/  VCAarg; } ;
struct cx24123_bandselect_val {int VCOdivider; scalar_t__ symbolrate_low; scalar_t__ symbolrate_high; int freq_low; int freq_high; int /*<<< orphan*/  progdata; int /*<<< orphan*/  FILTune; int /*<<< orphan*/  VGAprogdata; int /*<<< orphan*/  VCAprogdata; } ;
struct cx24123_AGC_val {int VCOdivider; scalar_t__ symbolrate_low; scalar_t__ symbolrate_high; int freq_low; int freq_high; int /*<<< orphan*/  progdata; int /*<<< orphan*/  FILTune; int /*<<< orphan*/  VGAprogdata; int /*<<< orphan*/  VCAprogdata; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct cx24123_bandselect_val*) ; 
 int XTAL ; 
 struct cx24123_bandselect_val* cx24123_AGC_vals ; 
 struct cx24123_bandselect_val* cx24123_bandselect_vals ; 
 int force_band ; 

__attribute__((used)) static int cx24123_pll_calculate(struct dvb_frontend *fe)
{
	struct dtv_frontend_properties *p = &fe->dtv_property_cache;
	struct cx24123_state *state = fe->demodulator_priv;
	u32 ndiv = 0, adiv = 0, vco_div = 0;
	int i = 0;
	int pump = 2;
	int band = 0;
	int num_bands = ARRAY_SIZE(cx24123_bandselect_vals);
	struct cx24123_bandselect_val *bsv = NULL;
	struct cx24123_AGC_val *agcv = NULL;

	/* Defaults for low freq, low rate */
	state->VCAarg = cx24123_AGC_vals[0].VCAprogdata;
	state->VGAarg = cx24123_AGC_vals[0].VGAprogdata;
	state->bandselectarg = cx24123_bandselect_vals[0].progdata;
	vco_div = cx24123_bandselect_vals[0].VCOdivider;

	/* For the given symbol rate, determine the VCA, VGA and
	 * FILTUNE programming bits */
	for (i = 0; i < ARRAY_SIZE(cx24123_AGC_vals); i++) {
		agcv = &cx24123_AGC_vals[i];
		if ((agcv->symbolrate_low <= p->symbol_rate) &&
		    (agcv->symbolrate_high >= p->symbol_rate)) {
			state->VCAarg = agcv->VCAprogdata;
			state->VGAarg = agcv->VGAprogdata;
			state->FILTune = agcv->FILTune;
		}
	}

	/* determine the band to use */
	if (force_band < 1 || force_band > num_bands) {
		for (i = 0; i < num_bands; i++) {
			bsv = &cx24123_bandselect_vals[i];
			if ((bsv->freq_low <= p->frequency) &&
				(bsv->freq_high >= p->frequency))
				band = i;
		}
	} else
		band = force_band - 1;

	state->bandselectarg = cx24123_bandselect_vals[band].progdata;
	vco_div = cx24123_bandselect_vals[band].VCOdivider;

	/* determine the charge pump current */
	if (p->frequency < (cx24123_bandselect_vals[band].freq_low +
		cx24123_bandselect_vals[band].freq_high) / 2)
		pump = 0x01;
	else
		pump = 0x02;

	/* Determine the N/A dividers for the requested lband freq (in kHz). */
	/* Note: the reference divider R=10, frequency is in KHz,
	 * XTAL is in Hz */
	ndiv = (((p->frequency * vco_div * 10) /
		(2 * XTAL / 1000)) / 32) & 0x1ff;
	adiv = (((p->frequency * vco_div * 10) /
		(2 * XTAL / 1000)) % 32) & 0x1f;

	if (adiv == 0 && ndiv > 0)
		ndiv--;

	/* control bits 11, refdiv 11, charge pump polarity 1,
	 * charge pump current, ndiv, adiv */
	state->pllarg = (3 << 19) | (3 << 17) | (1 << 16) |
		(pump << 14) | (ndiv << 5) | adiv;

	return 0;
}