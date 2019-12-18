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
struct stv0900_internal {int chip_id; int* symbol_rate; int* srch_algo; int mclk; int* srch_range; scalar_t__* srch_standard; } ;
typedef  int s16 ;
typedef  enum fe_stv0900_demod_num { ____Placeholder_fe_stv0900_demod_num } fe_stv0900_demod_num ;

/* Variables and functions */
 int /*<<< orphan*/  CARCFG ; 
 int /*<<< orphan*/  CARFREQ ; 
 int /*<<< orphan*/  CARHDR ; 
 int /*<<< orphan*/  CFRINIT0 ; 
 int /*<<< orphan*/  CFRINIT1 ; 
 int /*<<< orphan*/  CFRLOW0 ; 
 int /*<<< orphan*/  CFRLOW1 ; 
 int /*<<< orphan*/  CFRUP0 ; 
 int /*<<< orphan*/  CFRUP1 ; 
 int /*<<< orphan*/  CFR_AUTOSCAN ; 
 int /*<<< orphan*/  CFR_LOW0 ; 
 int /*<<< orphan*/  CFR_LOW1 ; 
 int /*<<< orphan*/  CFR_UP0 ; 
 int /*<<< orphan*/  CFR_UP1 ; 
 int /*<<< orphan*/  CORRELEXP ; 
 int /*<<< orphan*/  DEMOD_MODE ; 
 int /*<<< orphan*/  DMDISTATE ; 
 int /*<<< orphan*/  EQUALCFG ; 
 int /*<<< orphan*/  FFECFG ; 
 int LSB (int) ; 
 int MSB (int) ; 
 int /*<<< orphan*/  RTC ; 
 int /*<<< orphan*/  RTCS2 ; 
 int /*<<< orphan*/  S1S2_SEQUENTIAL ; 
 int /*<<< orphan*/  SCAN_ENABLE ; 
 int /*<<< orphan*/  SFRSTEP ; 
 scalar_t__ STV0900_AUTO_SEARCH ; 
#define  STV0900_COLD_START 129 
 scalar_t__ STV0900_SEARCH_DSS ; 
 scalar_t__ STV0900_SEARCH_DVBS1 ; 
#define  STV0900_WARM_START 128 
 int /*<<< orphan*/  TMGTHFALL ; 
 int /*<<< orphan*/  TMGTHRISE ; 
 int /*<<< orphan*/  VAVSRVIT ; 
 int /*<<< orphan*/  VITSCALE ; 
 int /*<<< orphan*/  stv0900_write_bits (struct stv0900_internal*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stv0900_write_reg (struct stv0900_internal*,int /*<<< orphan*/ ,int) ; 

void stv0900_start_search(struct stv0900_internal *intp,
				enum fe_stv0900_demod_num demod)
{
	u32 freq;
	s16 freq_s16 ;

	stv0900_write_bits(intp, DEMOD_MODE, 0x1f);
	if (intp->chip_id == 0x10)
		stv0900_write_reg(intp, CORRELEXP, 0xaa);

	if (intp->chip_id < 0x20)
		stv0900_write_reg(intp, CARHDR, 0x55);

	if (intp->chip_id <= 0x20) {
		if (intp->symbol_rate[0] <= 5000000) {
			stv0900_write_reg(intp, CARCFG, 0x44);
			stv0900_write_reg(intp, CFRUP1, 0x0f);
			stv0900_write_reg(intp, CFRUP0, 0xff);
			stv0900_write_reg(intp, CFRLOW1, 0xf0);
			stv0900_write_reg(intp, CFRLOW0, 0x00);
			stv0900_write_reg(intp, RTCS2, 0x68);
		} else {
			stv0900_write_reg(intp, CARCFG, 0xc4);
			stv0900_write_reg(intp, RTCS2, 0x44);
		}

	} else { /*cut 3.0 above*/
		if (intp->symbol_rate[demod] <= 5000000)
			stv0900_write_reg(intp, RTCS2, 0x68);
		else
			stv0900_write_reg(intp, RTCS2, 0x44);

		stv0900_write_reg(intp, CARCFG, 0x46);
		if (intp->srch_algo[demod] == STV0900_WARM_START) {
			freq = 1000 << 16;
			freq /= (intp->mclk / 1000);
			freq_s16 = (s16)freq;
		} else {
			freq = (intp->srch_range[demod] / 2000);
			if (intp->symbol_rate[demod] <= 5000000)
				freq += 80;
			else
				freq += 600;

			freq = freq << 16;
			freq /= (intp->mclk / 1000);
			freq_s16 = (s16)freq;
		}

		stv0900_write_bits(intp, CFR_UP1, MSB(freq_s16));
		stv0900_write_bits(intp, CFR_UP0, LSB(freq_s16));
		freq_s16 *= (-1);
		stv0900_write_bits(intp, CFR_LOW1, MSB(freq_s16));
		stv0900_write_bits(intp, CFR_LOW0, LSB(freq_s16));
	}

	stv0900_write_reg(intp, CFRINIT1, 0);
	stv0900_write_reg(intp, CFRINIT0, 0);

	if (intp->chip_id >= 0x20) {
		stv0900_write_reg(intp, EQUALCFG, 0x41);
		stv0900_write_reg(intp, FFECFG, 0x41);

		if ((intp->srch_standard[demod] == STV0900_SEARCH_DVBS1) ||
			(intp->srch_standard[demod] == STV0900_SEARCH_DSS) ||
			(intp->srch_standard[demod] == STV0900_AUTO_SEARCH)) {
			stv0900_write_reg(intp, VITSCALE,
								0x82);
			stv0900_write_reg(intp, VAVSRVIT, 0x0);
		}
	}

	stv0900_write_reg(intp, SFRSTEP, 0x00);
	stv0900_write_reg(intp, TMGTHRISE, 0xe0);
	stv0900_write_reg(intp, TMGTHFALL, 0xc0);
	stv0900_write_bits(intp, SCAN_ENABLE, 0);
	stv0900_write_bits(intp, CFR_AUTOSCAN, 0);
	stv0900_write_bits(intp, S1S2_SEQUENTIAL, 0);
	stv0900_write_reg(intp, RTC, 0x88);
	if (intp->chip_id >= 0x20) {
		if (intp->symbol_rate[demod] < 2000000) {
			if (intp->chip_id <= 0x20)
				stv0900_write_reg(intp, CARFREQ, 0x39);
			else  /*cut 3.0*/
				stv0900_write_reg(intp, CARFREQ, 0x89);

			stv0900_write_reg(intp, CARHDR, 0x40);
		} else if (intp->symbol_rate[demod] < 10000000) {
			stv0900_write_reg(intp, CARFREQ, 0x4c);
			stv0900_write_reg(intp, CARHDR, 0x20);
		} else {
			stv0900_write_reg(intp, CARFREQ, 0x4b);
			stv0900_write_reg(intp, CARHDR, 0x20);
		}

	} else {
		if (intp->symbol_rate[demod] < 10000000)
			stv0900_write_reg(intp, CARFREQ, 0xef);
		else
			stv0900_write_reg(intp, CARFREQ, 0xed);
	}

	switch (intp->srch_algo[demod]) {
	case STV0900_WARM_START:
		stv0900_write_reg(intp, DMDISTATE, 0x1f);
		stv0900_write_reg(intp, DMDISTATE, 0x18);
		break;
	case STV0900_COLD_START:
		stv0900_write_reg(intp, DMDISTATE, 0x1f);
		stv0900_write_reg(intp, DMDISTATE, 0x15);
		break;
	default:
		break;
	}
}