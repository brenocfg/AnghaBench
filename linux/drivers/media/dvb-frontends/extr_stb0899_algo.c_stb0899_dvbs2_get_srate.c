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
struct stb0899_internal {int master_clk; } ;
struct stb0899_state {struct stb0899_config* config; struct stb0899_internal internal; } ;
struct stb0899_config {int btr_nco_bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTR_NOM_FREQ ; 
 int /*<<< orphan*/  DECIM_CNTRL ; 
 int /*<<< orphan*/  DECIM_RATE ; 
 int STB0899_GETFIELD (int /*<<< orphan*/ ,int) ; 
 int STB0899_READ_S2REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STB0899_S2DEMOD ; 

__attribute__((used)) static u32 stb0899_dvbs2_get_srate(struct stb0899_state *state)
{
	struct stb0899_internal *internal = &state->internal;
	struct stb0899_config *config = state->config;

	u32 bTrNomFreq, srate, decimRate, intval1, intval2, reg;
	int div1, div2, rem1, rem2;

	div1 = config->btr_nco_bits / 2;
	div2 = config->btr_nco_bits - div1 - 1;

	bTrNomFreq = STB0899_READ_S2REG(STB0899_S2DEMOD, BTR_NOM_FREQ);

	reg = STB0899_READ_S2REG(STB0899_S2DEMOD, DECIM_CNTRL);
	decimRate = STB0899_GETFIELD(DECIM_RATE, reg);
	decimRate = (1 << decimRate);

	intval1 = internal->master_clk / (1 << div1);
	intval2 = bTrNomFreq / (1 << div2);

	rem1 = internal->master_clk % (1 << div1);
	rem2 = bTrNomFreq % (1 << div2);
	/* only for integer calculation	*/
	srate = (intval1 * intval2) + ((intval1 * rem2) / (1 << div2)) + ((intval2 * rem1) / (1 << div1));
	srate /= decimRate;	/*symbrate = (btrnomfreq_register_val*MasterClock)/2^(27+decim_rate_field) */

	return	srate;
}