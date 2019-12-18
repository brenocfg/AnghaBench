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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int u16 ;

/* Variables and functions */
 int EBADMSG ; 
 int FMC2_BCHDSR0_DEF ; 
 int FMC2_BCHDSR0_DEN_MASK ; 
 int FMC2_BCHDSR0_DEN_SHIFT ; 
 int FMC2_BCHDSR0_DUE ; 
 int FMC2_BCHDSR1_EBP1_MASK ; 
 int FMC2_BCHDSR1_EBP2_MASK ; 
 int FMC2_BCHDSR1_EBP2_SHIFT ; 
 int FMC2_BCHDSR2_EBP3_MASK ; 
 int FMC2_BCHDSR2_EBP4_MASK ; 
 int FMC2_BCHDSR2_EBP4_SHIFT ; 
 int FMC2_BCHDSR3_EBP5_MASK ; 
 int FMC2_BCHDSR3_EBP6_MASK ; 
 int FMC2_BCHDSR3_EBP6_SHIFT ; 
 int FMC2_BCHDSR4_EBP7_MASK ; 
 int FMC2_BCHDSR4_EBP8_MASK ; 
 int FMC2_BCHDSR4_EBP8_SHIFT ; 
 int /*<<< orphan*/  change_bit (int,unsigned long*) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int stm32_fmc2_bch_decode(int eccsize, u8 *dat, u32 *ecc_sta)
{
	u32 bchdsr0 = ecc_sta[0];
	u32 bchdsr1 = ecc_sta[1];
	u32 bchdsr2 = ecc_sta[2];
	u32 bchdsr3 = ecc_sta[3];
	u32 bchdsr4 = ecc_sta[4];
	u16 pos[8];
	int i, den;
	unsigned int nb_errs = 0;

	/* No errors found */
	if (likely(!(bchdsr0 & FMC2_BCHDSR0_DEF)))
		return 0;

	/* Too many errors detected */
	if (unlikely(bchdsr0 & FMC2_BCHDSR0_DUE))
		return -EBADMSG;

	pos[0] = bchdsr1 & FMC2_BCHDSR1_EBP1_MASK;
	pos[1] = (bchdsr1 & FMC2_BCHDSR1_EBP2_MASK) >> FMC2_BCHDSR1_EBP2_SHIFT;
	pos[2] = bchdsr2 & FMC2_BCHDSR2_EBP3_MASK;
	pos[3] = (bchdsr2 & FMC2_BCHDSR2_EBP4_MASK) >> FMC2_BCHDSR2_EBP4_SHIFT;
	pos[4] = bchdsr3 & FMC2_BCHDSR3_EBP5_MASK;
	pos[5] = (bchdsr3 & FMC2_BCHDSR3_EBP6_MASK) >> FMC2_BCHDSR3_EBP6_SHIFT;
	pos[6] = bchdsr4 & FMC2_BCHDSR4_EBP7_MASK;
	pos[7] = (bchdsr4 & FMC2_BCHDSR4_EBP8_MASK) >> FMC2_BCHDSR4_EBP8_SHIFT;

	den = (bchdsr0 & FMC2_BCHDSR0_DEN_MASK) >> FMC2_BCHDSR0_DEN_SHIFT;
	for (i = 0; i < den; i++) {
		if (pos[i] < eccsize * 8) {
			change_bit(pos[i], (unsigned long *)dat);
			nb_errs++;
		}
	}

	return nb_errs;
}