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
struct stv0900_internal {int* srch_standard; int chip_id; } ;
typedef  int s32 ;
typedef  enum fe_stv0900_demod_num { ____Placeholder_fe_stv0900_demod_num } fe_stv0900_demod_num ;

/* Variables and functions */
 int /*<<< orphan*/  CARFREQ ; 
 int /*<<< orphan*/  CORRELABS ; 
 int /*<<< orphan*/  DMDCFGMD ; 
 int FALSE ; 
 int /*<<< orphan*/  FLYWHEEL_CPT ; 
 int /*<<< orphan*/  HEADER_MODE ; 
#define  STV0900_AUTO_SEARCH 131 
 int STV0900_DVBS2_FOUND ; 
#define  STV0900_SEARCH_DSS 130 
#define  STV0900_SEARCH_DVBS1 129 
#define  STV0900_SEARCH_DVBS2 128 
 int TRUE ; 
 int /*<<< orphan*/  msleep (int) ; 
 int stv0900_check_signal_presence (struct stv0900_internal*,int) ; 
 int stv0900_get_bits (struct stv0900_internal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stv0900_get_sw_loop_params (struct stv0900_internal*,int*,int*,int*,int) ; 
 int stv0900_search_carr_sw_loop (struct stv0900_internal*,int,int,int,int,int) ; 
 int /*<<< orphan*/  stv0900_write_reg (struct stv0900_internal*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int stv0900_sw_algo(struct stv0900_internal *intp,
				enum fe_stv0900_demod_num demod)
{
	int	lock = FALSE,
		no_signal,
		zigzag;
	s32	s2fw,
		fqc_inc,
		sft_stp_tout,
		trial_cntr,
		max_steps;

	stv0900_get_sw_loop_params(intp, &fqc_inc, &sft_stp_tout,
					&max_steps, demod);
	switch (intp->srch_standard[demod]) {
	case STV0900_SEARCH_DVBS1:
	case STV0900_SEARCH_DSS:
		if (intp->chip_id >= 0x20)
			stv0900_write_reg(intp, CARFREQ, 0x3b);
		else
			stv0900_write_reg(intp, CARFREQ, 0xef);

		stv0900_write_reg(intp, DMDCFGMD, 0x49);
		zigzag = FALSE;
		break;
	case STV0900_SEARCH_DVBS2:
		if (intp->chip_id >= 0x20)
			stv0900_write_reg(intp, CORRELABS, 0x79);
		else
			stv0900_write_reg(intp, CORRELABS, 0x68);

		stv0900_write_reg(intp, DMDCFGMD, 0x89);

		zigzag = TRUE;
		break;
	case STV0900_AUTO_SEARCH:
	default:
		if (intp->chip_id >= 0x20) {
			stv0900_write_reg(intp, CARFREQ, 0x3b);
			stv0900_write_reg(intp, CORRELABS, 0x79);
		} else {
			stv0900_write_reg(intp, CARFREQ, 0xef);
			stv0900_write_reg(intp, CORRELABS, 0x68);
		}

		stv0900_write_reg(intp, DMDCFGMD, 0xc9);
		zigzag = FALSE;
		break;
	}

	trial_cntr = 0;
	do {
		lock = stv0900_search_carr_sw_loop(intp,
						fqc_inc,
						sft_stp_tout,
						zigzag,
						max_steps,
						demod);
		no_signal = stv0900_check_signal_presence(intp, demod);
		trial_cntr++;
		if ((lock == TRUE)
				|| (no_signal == TRUE)
				|| (trial_cntr == 2)) {

			if (intp->chip_id >= 0x20) {
				stv0900_write_reg(intp, CARFREQ, 0x49);
				stv0900_write_reg(intp, CORRELABS, 0x9e);
			} else {
				stv0900_write_reg(intp, CARFREQ, 0xed);
				stv0900_write_reg(intp, CORRELABS, 0x88);
			}

			if ((stv0900_get_bits(intp, HEADER_MODE) ==
						STV0900_DVBS2_FOUND) &&
							(lock == TRUE)) {
				msleep(sft_stp_tout);
				s2fw = stv0900_get_bits(intp, FLYWHEEL_CPT);

				if (s2fw < 0xd) {
					msleep(sft_stp_tout);
					s2fw = stv0900_get_bits(intp,
								FLYWHEEL_CPT);
				}

				if (s2fw < 0xd) {
					lock = FALSE;

					if (trial_cntr < 2) {
						if (intp->chip_id >= 0x20)
							stv0900_write_reg(intp,
								CORRELABS,
								0x79);
						else
							stv0900_write_reg(intp,
								CORRELABS,
								0x68);

						stv0900_write_reg(intp,
								DMDCFGMD,
								0x89);
					}
				}
			}
		}

	} while ((lock == FALSE)
		&& (trial_cntr < 2)
		&& (no_signal == FALSE));

	return lock;
}