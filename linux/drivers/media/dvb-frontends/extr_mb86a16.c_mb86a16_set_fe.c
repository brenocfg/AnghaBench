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
typedef  unsigned char u8 ;
struct mb86a16_state {unsigned char frequency; unsigned char srate; int master_clk; } ;

/* Variables and functions */
 scalar_t__ AFCEXEN_set (struct mb86a16_state*,unsigned char,int) ; 
 scalar_t__ CNTM_set (struct mb86a16_state*,unsigned char,unsigned char,unsigned char) ; 
 scalar_t__ DAGC_data_set (struct mb86a16_state*,int,int) ; 
 scalar_t__ EN_set (struct mb86a16_state*,unsigned char,unsigned char) ; 
 int EREMOTEIO ; 
 int /*<<< orphan*/  FEC_srst (struct mb86a16_state*) ; 
 int /*<<< orphan*/  MB86A16_DEBUG ; 
 int /*<<< orphan*/  MB86A16_ERROR ; 
 int /*<<< orphan*/  MB86A16_INFO ; 
 scalar_t__ S01T_set (struct mb86a16_state*,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  S2T_set (struct mb86a16_state*,unsigned char) ; 
 int /*<<< orphan*/  S45T_set (struct mb86a16_state*,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  SEQ_set (struct mb86a16_state*,int) ; 
 int /*<<< orphan*/  Vi_set (struct mb86a16_state*,unsigned char,unsigned char) ; 
 int abs (int) ; 
 int afcerr_chk (struct mb86a16_state*) ; 
 scalar_t__ afcex_data_set (struct mb86a16_state*,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  afcex_info_get (struct mb86a16_state*,int,unsigned char*,unsigned char*) ; 
 scalar_t__ afcofs_data_set (struct mb86a16_state*,unsigned char,unsigned char) ; 
 int dagcm_val_get (struct mb86a16_state*) ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,...) ; 
 int /*<<< orphan*/  freqerr_chk (struct mb86a16_state*,int,int,int) ; 
 scalar_t__ initial_set (struct mb86a16_state*) ; 
 int /*<<< orphan*/  iq_vt_set (struct mb86a16_state*,int) ; 
 int mb86a16_read (struct mb86a16_state*,int,unsigned char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 scalar_t__ rf_val_set (struct mb86a16_state*,int,int,unsigned char) ; 
 int signal_det (struct mb86a16_state*,int,unsigned char*) ; 
 int /*<<< orphan*/  smrt_info_get (struct mb86a16_state*,int) ; 
 scalar_t__ smrt_set (struct mb86a16_state*,int) ; 
 scalar_t__ srst (struct mb86a16_state*) ; 
 int swp_freq_calcuation (struct mb86a16_state*,int,int,int*,int,int,unsigned char,int,int,int,unsigned char*) ; 
 int /*<<< orphan*/  swp_info_get (struct mb86a16_state*,int,int,int,unsigned char,int,int*,int*,unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  swp_info_get2 (struct mb86a16_state*,int,unsigned char,int,int*,int*,unsigned char*,unsigned char*) ; 
 int sync_chk (struct mb86a16_state*,unsigned char*) ; 
 int /*<<< orphan*/  udelay (int) ; 
 unsigned char vco_dev_get (struct mb86a16_state*,int) ; 
 int /*<<< orphan*/  verbose ; 

__attribute__((used)) static int mb86a16_set_fe(struct mb86a16_state *state)
{
	u8 agcval, cnmval;

	int i, j;
	int fOSC = 0;
	int fOSC_start = 0;
	int wait_t;
	int fcp;
	int swp_ofs;
	int V[60];
	u8 SIG1MIN;

	unsigned char CREN, AFCEN, AFCEXEN;
	unsigned char SIG1;
	unsigned char TIMINT1, TIMINT2, TIMEXT;
	unsigned char S0T, S1T;
	unsigned char S2T;
/*	unsigned char S2T, S3T; */
	unsigned char S4T, S5T;
	unsigned char AFCEX_L, AFCEX_H;
	unsigned char R;
	unsigned char VIRM;
	unsigned char ETH, VIA;
	unsigned char junk;

	int loop;
	int ftemp;
	int v, vmax, vmin;
	int vmax_his, vmin_his;
	int swp_freq, prev_swp_freq[20];
	int prev_freq_num;
	int signal_dupl;
	int afcex_freq;
	int signal;
	int afcerr;
	int temp_freq, delta_freq;
	int dagcm[4];
	int smrt_d;
/*	int freq_err; */
	int n;
	int ret = -1;
	int sync;

	dprintk(verbose, MB86A16_INFO, 1, "freq=%d Mhz, symbrt=%d Ksps", state->frequency, state->srate);

	fcp = 3000;
	swp_ofs = state->srate / 4;

	for (i = 0; i < 60; i++)
		V[i] = -1;

	for (i = 0; i < 20; i++)
		prev_swp_freq[i] = 0;

	SIG1MIN = 25;

	for (n = 0; ((n < 3) && (ret == -1)); n++) {
		SEQ_set(state, 0);
		iq_vt_set(state, 0);

		CREN = 0;
		AFCEN = 0;
		AFCEXEN = 1;
		TIMINT1 = 0;
		TIMINT2 = 1;
		TIMEXT = 2;
		S1T = 0;
		S0T = 0;

		if (initial_set(state) < 0) {
			dprintk(verbose, MB86A16_ERROR, 1, "initial set failed");
			return -1;
		}
		if (DAGC_data_set(state, 3, 2) < 0) {
			dprintk(verbose, MB86A16_ERROR, 1, "DAGC data set error");
			return -1;
		}
		if (EN_set(state, CREN, AFCEN) < 0) {
			dprintk(verbose, MB86A16_ERROR, 1, "EN set error");
			return -1; /* (0, 0) */
		}
		if (AFCEXEN_set(state, AFCEXEN, state->srate) < 0) {
			dprintk(verbose, MB86A16_ERROR, 1, "AFCEXEN set error");
			return -1; /* (1, smrt) = (1, symbolrate) */
		}
		if (CNTM_set(state, TIMINT1, TIMINT2, TIMEXT) < 0) {
			dprintk(verbose, MB86A16_ERROR, 1, "CNTM set error");
			return -1; /* (0, 1, 2) */
		}
		if (S01T_set(state, S1T, S0T) < 0) {
			dprintk(verbose, MB86A16_ERROR, 1, "S01T set error");
			return -1; /* (0, 0) */
		}
		smrt_info_get(state, state->srate);
		if (smrt_set(state, state->srate) < 0) {
			dprintk(verbose, MB86A16_ERROR, 1, "smrt info get error");
			return -1;
		}

		R = vco_dev_get(state, state->srate);
		if (R == 1)
			fOSC_start = state->frequency;

		else if (R == 0) {
			if (state->frequency % 2 == 0) {
				fOSC_start = state->frequency;
			} else {
				fOSC_start = state->frequency + 1;
				if (fOSC_start > 2150)
					fOSC_start = state->frequency - 1;
			}
		}
		loop = 1;
		ftemp = fOSC_start * 1000;
		vmax = 0 ;
		while (loop == 1) {
			ftemp = ftemp + swp_ofs;
			vmax++;

			/* Upper bound */
			if (ftemp > 2150000) {
				loop = 0;
				vmax--;
			} else {
				if ((ftemp == 2150000) ||
				    (ftemp - state->frequency * 1000 >= fcp + state->srate / 4))
					loop = 0;
			}
		}

		loop = 1;
		ftemp = fOSC_start * 1000;
		vmin = 0 ;
		while (loop == 1) {
			ftemp = ftemp - swp_ofs;
			vmin--;

			/* Lower bound */
			if (ftemp < 950000) {
				loop = 0;
				vmin++;
			} else {
				if ((ftemp == 950000) ||
				    (state->frequency * 1000 - ftemp >= fcp + state->srate / 4))
					loop = 0;
			}
		}

		wait_t = (8000 + state->srate / 2) / state->srate;
		if (wait_t == 0)
			wait_t = 1;

		i = 0;
		j = 0;
		prev_freq_num = 0;
		loop = 1;
		signal = 0;
		vmax_his = 0;
		vmin_his = 0;
		v = 0;

		while (loop == 1) {
			swp_info_get(state, fOSC_start, state->srate,
				     v, R, swp_ofs, &fOSC,
				     &afcex_freq, &AFCEX_L, &AFCEX_H);

			udelay(100);
			if (rf_val_set(state, fOSC, state->srate, R) < 0) {
				dprintk(verbose, MB86A16_ERROR, 1, "rf val set error");
				return -1;
			}
			udelay(100);
			if (afcex_data_set(state, AFCEX_L, AFCEX_H) < 0) {
				dprintk(verbose, MB86A16_ERROR, 1, "afcex data set error");
				return -1;
			}
			if (srst(state) < 0) {
				dprintk(verbose, MB86A16_ERROR, 1, "srst error");
				return -1;
			}
			msleep_interruptible(wait_t);

			if (mb86a16_read(state, 0x37, &SIG1) != 2) {
				dprintk(verbose, MB86A16_ERROR, 1, "I2C transfer error");
				return -1;
			}
			V[30 + v] = SIG1 ;
			swp_freq = swp_freq_calcuation(state, i, v, V, vmax, vmin,
						      SIG1MIN, fOSC, afcex_freq,
						      swp_ofs, &SIG1);	/* changed */

			signal_dupl = 0;
			for (j = 0; j < prev_freq_num; j++) {
				if ((abs(prev_swp_freq[j] - swp_freq)) < (swp_ofs * 3 / 2)) {
					signal_dupl = 1;
					dprintk(verbose, MB86A16_INFO, 1, "Probably Duplicate Signal, j = %d", j);
				}
			}
			if ((signal_dupl == 0) && (swp_freq > 0) && (abs(swp_freq - state->frequency * 1000) < fcp + state->srate / 6)) {
				dprintk(verbose, MB86A16_DEBUG, 1, "------ Signal detect ------ [swp_freq=[%07d, srate=%05d]]", swp_freq, state->srate);
				prev_swp_freq[prev_freq_num] = swp_freq;
				prev_freq_num++;
				swp_info_get2(state, state->srate, R, swp_freq,
					      &afcex_freq, &fOSC,
					      &AFCEX_L, &AFCEX_H);

				if (rf_val_set(state, fOSC, state->srate, R) < 0) {
					dprintk(verbose, MB86A16_ERROR, 1, "rf val set error");
					return -1;
				}
				if (afcex_data_set(state, AFCEX_L, AFCEX_H) < 0) {
					dprintk(verbose, MB86A16_ERROR, 1, "afcex data set error");
					return -1;
				}
				signal = signal_det(state, state->srate, &SIG1);
				if (signal == 1) {
					dprintk(verbose, MB86A16_ERROR, 1, "***** Signal Found *****");
					loop = 0;
				} else {
					dprintk(verbose, MB86A16_ERROR, 1, "!!!!! No signal !!!!!, try again...");
					smrt_info_get(state, state->srate);
					if (smrt_set(state, state->srate) < 0) {
						dprintk(verbose, MB86A16_ERROR, 1, "smrt set error");
						return -1;
					}
				}
			}
			if (v > vmax)
				vmax_his = 1 ;
			if (v < vmin)
				vmin_his = 1 ;
			i++;

			if ((i % 2 == 1) && (vmax_his == 1))
				i++;
			if ((i % 2 == 0) && (vmin_his == 1))
				i++;

			if (i % 2 == 1)
				v = (i + 1) / 2;
			else
				v = -i / 2;

			if ((vmax_his == 1) && (vmin_his == 1))
				loop = 0 ;
		}

		if (signal == 1) {
			dprintk(verbose, MB86A16_INFO, 1, " Start Freq Error Check");
			S1T = 7 ;
			S0T = 1 ;
			CREN = 0 ;
			AFCEN = 1 ;
			AFCEXEN = 0 ;

			if (S01T_set(state, S1T, S0T) < 0) {
				dprintk(verbose, MB86A16_ERROR, 1, "S01T set error");
				return -1;
			}
			smrt_info_get(state, state->srate);
			if (smrt_set(state, state->srate) < 0) {
				dprintk(verbose, MB86A16_ERROR, 1, "smrt set error");
				return -1;
			}
			if (EN_set(state, CREN, AFCEN) < 0) {
				dprintk(verbose, MB86A16_ERROR, 1, "EN set error");
				return -1;
			}
			if (AFCEXEN_set(state, AFCEXEN, state->srate) < 0) {
				dprintk(verbose, MB86A16_ERROR, 1, "AFCEXEN set error");
				return -1;
			}
			afcex_info_get(state, afcex_freq, &AFCEX_L, &AFCEX_H);
			if (afcofs_data_set(state, AFCEX_L, AFCEX_H) < 0) {
				dprintk(verbose, MB86A16_ERROR, 1, "AFCOFS data set error");
				return -1;
			}
			if (srst(state) < 0) {
				dprintk(verbose, MB86A16_ERROR, 1, "srst error");
				return -1;
			}
			/* delay 4~200 */
			wait_t = 200000 / state->master_clk + 200000 / state->srate;
			msleep(wait_t);
			afcerr = afcerr_chk(state);
			if (afcerr == -1)
				return -1;

			swp_freq = fOSC * 1000 + afcerr ;
			AFCEXEN = 1 ;
			if (state->srate >= 1500)
				smrt_d = state->srate / 3;
			else
				smrt_d = state->srate / 2;
			smrt_info_get(state, smrt_d);
			if (smrt_set(state, smrt_d) < 0) {
				dprintk(verbose, MB86A16_ERROR, 1, "smrt set error");
				return -1;
			}
			if (AFCEXEN_set(state, AFCEXEN, smrt_d) < 0) {
				dprintk(verbose, MB86A16_ERROR, 1, "AFCEXEN set error");
				return -1;
			}
			R = vco_dev_get(state, smrt_d);
			if (DAGC_data_set(state, 2, 0) < 0) {
				dprintk(verbose, MB86A16_ERROR, 1, "DAGC data set error");
				return -1;
			}
			for (i = 0; i < 3; i++) {
				temp_freq = swp_freq + (i - 1) * state->srate / 8;
				swp_info_get2(state, smrt_d, R, temp_freq, &afcex_freq, &fOSC, &AFCEX_L, &AFCEX_H);
				if (rf_val_set(state, fOSC, smrt_d, R) < 0) {
					dprintk(verbose, MB86A16_ERROR, 1, "rf val set error");
					return -1;
				}
				if (afcex_data_set(state, AFCEX_L, AFCEX_H) < 0) {
					dprintk(verbose, MB86A16_ERROR, 1, "afcex data set error");
					return -1;
				}
				wait_t = 200000 / state->master_clk + 40000 / smrt_d;
				msleep(wait_t);
				dagcm[i] = dagcm_val_get(state);
			}
			if ((dagcm[0] > dagcm[1]) &&
			    (dagcm[0] > dagcm[2]) &&
			    (dagcm[0] - dagcm[1] > 2 * (dagcm[2] - dagcm[1]))) {

				temp_freq = swp_freq - 2 * state->srate / 8;
				swp_info_get2(state, smrt_d, R, temp_freq, &afcex_freq, &fOSC, &AFCEX_L, &AFCEX_H);
				if (rf_val_set(state, fOSC, smrt_d, R) < 0) {
					dprintk(verbose, MB86A16_ERROR, 1, "rf val set error");
					return -1;
				}
				if (afcex_data_set(state, AFCEX_L, AFCEX_H) < 0) {
					dprintk(verbose, MB86A16_ERROR, 1, "afcex data set");
					return -1;
				}
				wait_t = 200000 / state->master_clk + 40000 / smrt_d;
				msleep(wait_t);
				dagcm[3] = dagcm_val_get(state);
				if (dagcm[3] > dagcm[1])
					delta_freq = (dagcm[2] - dagcm[0] + dagcm[1] - dagcm[3]) * state->srate / 300;
				else
					delta_freq = 0;
			} else if ((dagcm[2] > dagcm[1]) &&
				   (dagcm[2] > dagcm[0]) &&
				   (dagcm[2] - dagcm[1] > 2 * (dagcm[0] - dagcm[1]))) {

				temp_freq = swp_freq + 2 * state->srate / 8;
				swp_info_get2(state, smrt_d, R, temp_freq, &afcex_freq, &fOSC, &AFCEX_L, &AFCEX_H);
				if (rf_val_set(state, fOSC, smrt_d, R) < 0) {
					dprintk(verbose, MB86A16_ERROR, 1, "rf val set");
					return -1;
				}
				if (afcex_data_set(state, AFCEX_L, AFCEX_H) < 0) {
					dprintk(verbose, MB86A16_ERROR, 1, "afcex data set");
					return -1;
				}
				wait_t = 200000 / state->master_clk + 40000 / smrt_d;
				msleep(wait_t);
				dagcm[3] = dagcm_val_get(state);
				if (dagcm[3] > dagcm[1])
					delta_freq = (dagcm[2] - dagcm[0] + dagcm[3] - dagcm[1]) * state->srate / 300;
				else
					delta_freq = 0 ;

			} else {
				delta_freq = 0 ;
			}
			dprintk(verbose, MB86A16_INFO, 1, "SWEEP Frequency = %d", swp_freq);
			swp_freq += delta_freq;
			dprintk(verbose, MB86A16_INFO, 1, "Adjusting .., DELTA Freq = %d, SWEEP Freq=%d", delta_freq, swp_freq);
			if (abs(state->frequency * 1000 - swp_freq) > 3800) {
				dprintk(verbose, MB86A16_INFO, 1, "NO  --  SIGNAL !");
			} else {

				S1T = 0;
				S0T = 3;
				CREN = 1;
				AFCEN = 0;
				AFCEXEN = 1;

				if (S01T_set(state, S1T, S0T) < 0) {
					dprintk(verbose, MB86A16_ERROR, 1, "S01T set error");
					return -1;
				}
				if (DAGC_data_set(state, 0, 0) < 0) {
					dprintk(verbose, MB86A16_ERROR, 1, "DAGC data set error");
					return -1;
				}
				R = vco_dev_get(state, state->srate);
				smrt_info_get(state, state->srate);
				if (smrt_set(state, state->srate) < 0) {
					dprintk(verbose, MB86A16_ERROR, 1, "smrt set error");
					return -1;
				}
				if (EN_set(state, CREN, AFCEN) < 0) {
					dprintk(verbose, MB86A16_ERROR, 1, "EN set error");
					return -1;
				}
				if (AFCEXEN_set(state, AFCEXEN, state->srate) < 0) {
					dprintk(verbose, MB86A16_ERROR, 1, "AFCEXEN set error");
					return -1;
				}
				swp_info_get2(state, state->srate, R, swp_freq, &afcex_freq, &fOSC, &AFCEX_L, &AFCEX_H);
				if (rf_val_set(state, fOSC, state->srate, R) < 0) {
					dprintk(verbose, MB86A16_ERROR, 1, "rf val set error");
					return -1;
				}
				if (afcex_data_set(state, AFCEX_L, AFCEX_H) < 0) {
					dprintk(verbose, MB86A16_ERROR, 1, "afcex data set error");
					return -1;
				}
				if (srst(state) < 0) {
					dprintk(verbose, MB86A16_ERROR, 1, "srst error");
					return -1;
				}
				wait_t = 7 + (10000 + state->srate / 2) / state->srate;
				if (wait_t == 0)
					wait_t = 1;
				msleep_interruptible(wait_t);
				if (mb86a16_read(state, 0x37, &SIG1) != 2) {
					dprintk(verbose, MB86A16_ERROR, 1, "I2C transfer error");
					return -EREMOTEIO;
				}

				if (SIG1 > 110) {
					S2T = 4; S4T = 1; S5T = 6; ETH = 4; VIA = 6;
					wait_t = 7 + (917504 + state->srate / 2) / state->srate;
				} else if (SIG1 > 105) {
					S2T = 4; S4T = 2; S5T = 8; ETH = 7; VIA = 2;
					wait_t = 7 + (1048576 + state->srate / 2) / state->srate;
				} else if (SIG1 > 85) {
					S2T = 5; S4T = 2; S5T = 8; ETH = 7; VIA = 2;
					wait_t = 7 + (1310720 + state->srate / 2) / state->srate;
				} else if (SIG1 > 65) {
					S2T = 6; S4T = 2; S5T = 8; ETH = 7; VIA = 2;
					wait_t = 7 + (1572864 + state->srate / 2) / state->srate;
				} else {
					S2T = 7; S4T = 2; S5T = 8; ETH = 7; VIA = 2;
					wait_t = 7 + (2097152 + state->srate / 2) / state->srate;
				}
				wait_t *= 2; /* FOS */
				S2T_set(state, S2T);
				S45T_set(state, S4T, S5T);
				Vi_set(state, ETH, VIA);
				srst(state);
				msleep_interruptible(wait_t);
				sync = sync_chk(state, &VIRM);
				dprintk(verbose, MB86A16_INFO, 1, "-------- Viterbi=[%d] SYNC=[%d] ---------", VIRM, sync);
				if (VIRM) {
					if (VIRM == 4) {
						/* 5/6 */
						if (SIG1 > 110)
							wait_t = (786432 + state->srate / 2) / state->srate;
						else
							wait_t = (1572864 + state->srate / 2) / state->srate;
						if (state->srate < 5000)
							/* FIXME ! , should be a long wait ! */
							msleep_interruptible(wait_t);
						else
							msleep_interruptible(wait_t);

						if (sync_chk(state, &junk) == 0) {
							iq_vt_set(state, 1);
							FEC_srst(state);
						}
					}
					/* 1/2, 2/3, 3/4, 7/8 */
					if (SIG1 > 110)
						wait_t = (786432 + state->srate / 2) / state->srate;
					else
						wait_t = (1572864 + state->srate / 2) / state->srate;
					msleep_interruptible(wait_t);
					SEQ_set(state, 1);
				} else {
					dprintk(verbose, MB86A16_INFO, 1, "NO  -- SYNC");
					SEQ_set(state, 1);
					ret = -1;
				}
			}
		} else {
			dprintk(verbose, MB86A16_INFO, 1, "NO  -- SIGNAL");
			ret = -1;
		}

		sync = sync_chk(state, &junk);
		if (sync) {
			dprintk(verbose, MB86A16_INFO, 1, "******* SYNC *******");
			freqerr_chk(state, state->frequency, state->srate, 1);
			ret = 0;
			break;
		}
	}

	mb86a16_read(state, 0x15, &agcval);
	mb86a16_read(state, 0x26, &cnmval);
	dprintk(verbose, MB86A16_INFO, 1, "AGC = %02x CNM = %02x", agcval, cnmval);

	return ret;
}