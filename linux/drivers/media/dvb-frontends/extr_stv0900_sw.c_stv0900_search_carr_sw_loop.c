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
struct stv0900_internal {int* srch_range; int mclk; int chip_id; } ;
typedef  int s32 ;
typedef  enum fe_stv0900_demod_num { ____Placeholder_fe_stv0900_demod_num } fe_stv0900_demod_num ;

/* Variables and functions */
 int /*<<< orphan*/  ALGOSWRST ; 
 int /*<<< orphan*/  CFRINIT0 ; 
 int /*<<< orphan*/  CFRINIT1 ; 
 int /*<<< orphan*/  DMDISTATE ; 
 int FALSE ; 
 int /*<<< orphan*/  RST_HWARE ; 
 int TRUE ; 
 int stv0900_check_signal_presence (struct stv0900_internal*,int) ; 
 int stv0900_get_demod_lock (struct stv0900_internal*,int,int) ; 
 int /*<<< orphan*/  stv0900_write_bits (struct stv0900_internal*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stv0900_write_reg (struct stv0900_internal*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int stv0900_search_carr_sw_loop(struct stv0900_internal *intp,
				s32 FreqIncr, s32 Timeout, int zigzag,
				s32 MaxStep, enum fe_stv0900_demod_num demod)
{
	int	no_signal,
		lock = FALSE;
	s32	stepCpt,
		freqOffset,
		max_carrier;

	max_carrier = intp->srch_range[demod] / 1000;
	max_carrier += (max_carrier / 10);

	max_carrier = 65536 * (max_carrier / 2);
	max_carrier /= intp->mclk / 1000;

	if (max_carrier > 0x4000)
		max_carrier = 0x4000;

	if (zigzag == TRUE)
		freqOffset = 0;
	else
		freqOffset = -max_carrier + FreqIncr;

	stepCpt = 0;

	do {
		stv0900_write_reg(intp, DMDISTATE, 0x1c);
		stv0900_write_reg(intp, CFRINIT1, (freqOffset / 256) & 0xff);
		stv0900_write_reg(intp, CFRINIT0, freqOffset & 0xff);
		stv0900_write_reg(intp, DMDISTATE, 0x18);
		stv0900_write_bits(intp, ALGOSWRST, 1);

		if (intp->chip_id == 0x12) {
			stv0900_write_bits(intp, RST_HWARE, 1);
			stv0900_write_bits(intp, RST_HWARE, 0);
		}

		if (zigzag == TRUE) {
			if (freqOffset >= 0)
				freqOffset = -freqOffset - 2 * FreqIncr;
			else
				freqOffset = -freqOffset;
		} else
			freqOffset += + 2 * FreqIncr;

		stepCpt++;
		lock = stv0900_get_demod_lock(intp, demod, Timeout);
		no_signal = stv0900_check_signal_presence(intp, demod);

	} while ((lock == FALSE)
			&& (no_signal == FALSE)
			&& ((freqOffset - FreqIncr) <  max_carrier)
			&& ((freqOffset + FreqIncr) > -max_carrier)
			&& (stepCpt < MaxStep));

	stv0900_write_bits(intp, ALGOSWRST, 0);

	return lock;
}