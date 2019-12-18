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
struct tsens_priv {int num_sensors; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BASE1_MASK ; 
 int BASE2_BKP_MASK ; 
 int BASE2_BKP_SHIFT ; 
 int BASE2_MASK ; 
 int BASE2_SHIFT ; 
 int BIT_APPEND ; 
 int BKP_REDUN_SEL ; 
 int BKP_REDUN_SHIFT ; 
 int BKP_SEL ; 
 int CAL_SEL_0_1 ; 
 int CAL_SEL_2 ; 
 int CAL_SEL_SHIFT ; 
 int CAL_SEL_SHIFT_2 ; 
 scalar_t__ IS_ERR (int*) ; 
#define  ONE_PT_CALIB 130 
#define  ONE_PT_CALIB2 129 
 int PTR_ERR (int*) ; 
 int S0_P1_MASK ; 
 int S0_P1_SHIFT ; 
 int S0_P2_BKP_MASK ; 
 int S0_P2_BKP_SHIFT ; 
 int S0_P2_MASK ; 
 int S0_P2_SHIFT ; 
 int S10_P1_BKP_SHIFT ; 
 int S10_P1_MASK ; 
 int S10_P1_MASK_BKP ; 
 int S10_P1_SHIFT ; 
 int S10_P2_BKP_MASK ; 
 int S10_P2_BKP_SHIFT ; 
 int S10_P2_MASK ; 
 int S10_P2_SHIFT ; 
 int S1_P1_MASK ; 
 int S1_P1_SHIFT ; 
 int S1_P2_BKP_MASK ; 
 int S1_P2_MASK ; 
 int S1_P2_SHIFT ; 
 int S2_P1_MASK ; 
 int S2_P1_SHIFT ; 
 int S2_P2_BKP_MASK ; 
 int S2_P2_BKP_SHIFT ; 
 int S2_P2_MASK ; 
 int S3_P1_MASK ; 
 int S3_P1_SHIFT ; 
 int S3_P2_BKP_MASK ; 
 int S3_P2_BKP_SHIFT ; 
 int S3_P2_MASK ; 
 int S3_P2_SHIFT ; 
 int S4_P1_MASK ; 
 int S4_P2_BKP_MASK ; 
 int S4_P2_BKP_SHIFT ; 
 int S4_P2_MASK ; 
 int S4_P2_SHIFT ; 
 int S5_P1_MASK ; 
 int S5_P1_SHIFT ; 
 int S5_P2_BKP_MASK ; 
 int S5_P2_BKP_SHIFT ; 
 int S5_P2_MASK ; 
 int S5_P2_SHIFT ; 
 int S6_P1_MASK ; 
 int S6_P1_SHIFT ; 
 int S6_P2_BKP_MASK ; 
 int S6_P2_MASK ; 
 int S6_P2_SHIFT ; 
 int S7_P1_MASK ; 
 int S7_P1_SHIFT ; 
 int S7_P2_BKP_MASK ; 
 int S7_P2_BKP_SHIFT ; 
 int S7_P2_MASK ; 
 int S8_P1_MASK ; 
 int S8_P1_MASK_BKP ; 
 int S8_P1_SHIFT ; 
 int S8_P2_BKP_MASK ; 
 int S8_P2_BKP_SHIFT ; 
 int S8_P2_MASK ; 
 int S8_P2_SHIFT ; 
 int S9_P1_BKP_SHIFT ; 
 int S9_P1_MASK ; 
 int S9_P1_MASK_BKP ; 
 int S9_P2_BKP_MASK ; 
 int S9_P2_BKP_SHIFT ; 
 int S9_P2_MASK ; 
 int S9_P2_SHIFT ; 
#define  TWO_PT_CALIB 128 
 int /*<<< orphan*/  compute_intercept_slope (struct tsens_priv*,int*,int*,int) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 scalar_t__ qfprom_read (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int calibrate_8974(struct tsens_priv *priv)
{
	int base1 = 0, base2 = 0, i;
	u32 p1[11], p2[11];
	int mode = 0;
	u32 *calib, *bkp;
	u32 calib_redun_sel;

	calib = (u32 *)qfprom_read(priv->dev, "calib");
	if (IS_ERR(calib))
		return PTR_ERR(calib);

	bkp = (u32 *)qfprom_read(priv->dev, "calib_backup");
	if (IS_ERR(bkp)) {
		kfree(calib);
		return PTR_ERR(bkp);
	}

	calib_redun_sel =  bkp[1] & BKP_REDUN_SEL;
	calib_redun_sel >>= BKP_REDUN_SHIFT;

	if (calib_redun_sel == BKP_SEL) {
		mode = (calib[4] & CAL_SEL_0_1) >> CAL_SEL_SHIFT;
		mode |= (calib[5] & CAL_SEL_2) >> CAL_SEL_SHIFT_2;

		switch (mode) {
		case TWO_PT_CALIB:
			base2 = (bkp[2] & BASE2_BKP_MASK) >> BASE2_BKP_SHIFT;
			p2[0] = (bkp[2] & S0_P2_BKP_MASK) >> S0_P2_BKP_SHIFT;
			p2[1] = (bkp[3] & S1_P2_BKP_MASK);
			p2[2] = (bkp[3] & S2_P2_BKP_MASK) >> S2_P2_BKP_SHIFT;
			p2[3] = (bkp[3] & S3_P2_BKP_MASK) >> S3_P2_BKP_SHIFT;
			p2[4] = (bkp[3] & S4_P2_BKP_MASK) >> S4_P2_BKP_SHIFT;
			p2[5] = (calib[4] & S5_P2_BKP_MASK) >> S5_P2_BKP_SHIFT;
			p2[6] = (calib[5] & S6_P2_BKP_MASK);
			p2[7] = (calib[5] & S7_P2_BKP_MASK) >> S7_P2_BKP_SHIFT;
			p2[8] = (calib[5] & S8_P2_BKP_MASK) >> S8_P2_BKP_SHIFT;
			p2[9] = (calib[5] & S9_P2_BKP_MASK) >> S9_P2_BKP_SHIFT;
			p2[10] = (calib[5] & S10_P2_BKP_MASK) >> S10_P2_BKP_SHIFT;
			/* Fall through */
		case ONE_PT_CALIB:
		case ONE_PT_CALIB2:
			base1 = bkp[0] & BASE1_MASK;
			p1[0] = (bkp[0] & S0_P1_MASK) >> S0_P1_SHIFT;
			p1[1] = (bkp[0] & S1_P1_MASK) >> S1_P1_SHIFT;
			p1[2] = (bkp[0] & S2_P1_MASK) >> S2_P1_SHIFT;
			p1[3] = (bkp[0] & S3_P1_MASK) >> S3_P1_SHIFT;
			p1[4] = (bkp[1] & S4_P1_MASK);
			p1[5] = (bkp[1] & S5_P1_MASK) >> S5_P1_SHIFT;
			p1[6] = (bkp[1] & S6_P1_MASK) >> S6_P1_SHIFT;
			p1[7] = (bkp[1] & S7_P1_MASK) >> S7_P1_SHIFT;
			p1[8] = (bkp[2] & S8_P1_MASK_BKP) >> S8_P1_SHIFT;
			p1[9] = (bkp[2] & S9_P1_MASK_BKP) >> S9_P1_BKP_SHIFT;
			p1[10] = (bkp[2] & S10_P1_MASK_BKP) >> S10_P1_BKP_SHIFT;
			break;
		}
	} else {
		mode = (calib[1] & CAL_SEL_0_1) >> CAL_SEL_SHIFT;
		mode |= (calib[3] & CAL_SEL_2) >> CAL_SEL_SHIFT_2;

		switch (mode) {
		case TWO_PT_CALIB:
			base2 = (calib[2] & BASE2_MASK) >> BASE2_SHIFT;
			p2[0] = (calib[2] & S0_P2_MASK) >> S0_P2_SHIFT;
			p2[1] = (calib[2] & S1_P2_MASK) >> S1_P2_SHIFT;
			p2[2] = (calib[3] & S2_P2_MASK);
			p2[3] = (calib[3] & S3_P2_MASK) >> S3_P2_SHIFT;
			p2[4] = (calib[3] & S4_P2_MASK) >> S4_P2_SHIFT;
			p2[5] = (calib[3] & S5_P2_MASK) >> S5_P2_SHIFT;
			p2[6] = (calib[3] & S6_P2_MASK) >> S6_P2_SHIFT;
			p2[7] = (calib[4] & S7_P2_MASK);
			p2[8] = (calib[4] & S8_P2_MASK) >> S8_P2_SHIFT;
			p2[9] = (calib[4] & S9_P2_MASK) >> S9_P2_SHIFT;
			p2[10] = (calib[4] & S10_P2_MASK) >> S10_P2_SHIFT;
			/* Fall through */
		case ONE_PT_CALIB:
		case ONE_PT_CALIB2:
			base1 = calib[0] & BASE1_MASK;
			p1[0] = (calib[0] & S0_P1_MASK) >> S0_P1_SHIFT;
			p1[1] = (calib[0] & S1_P1_MASK) >> S1_P1_SHIFT;
			p1[2] = (calib[0] & S2_P1_MASK) >> S2_P1_SHIFT;
			p1[3] = (calib[0] & S3_P1_MASK) >> S3_P1_SHIFT;
			p1[4] = (calib[1] & S4_P1_MASK);
			p1[5] = (calib[1] & S5_P1_MASK) >> S5_P1_SHIFT;
			p1[6] = (calib[1] & S6_P1_MASK) >> S6_P1_SHIFT;
			p1[7] = (calib[1] & S7_P1_MASK) >> S7_P1_SHIFT;
			p1[8] = (calib[1] & S8_P1_MASK) >> S8_P1_SHIFT;
			p1[9] = (calib[2] & S9_P1_MASK);
			p1[10] = (calib[2] & S10_P1_MASK) >> S10_P1_SHIFT;
			break;
		}
	}

	switch (mode) {
	case ONE_PT_CALIB:
		for (i = 0; i < priv->num_sensors; i++)
			p1[i] += (base1 << 2) | BIT_APPEND;
		break;
	case TWO_PT_CALIB:
		for (i = 0; i < priv->num_sensors; i++) {
			p2[i] += base2;
			p2[i] <<= 2;
			p2[i] |= BIT_APPEND;
		}
		/* Fall through */
	case ONE_PT_CALIB2:
		for (i = 0; i < priv->num_sensors; i++) {
			p1[i] += base1;
			p1[i] <<= 2;
			p1[i] |= BIT_APPEND;
		}
		break;
	default:
		for (i = 0; i < priv->num_sensors; i++)
			p2[i] = 780;
		p1[0] = 502;
		p1[1] = 509;
		p1[2] = 503;
		p1[3] = 509;
		p1[4] = 505;
		p1[5] = 509;
		p1[6] = 507;
		p1[7] = 510;
		p1[8] = 508;
		p1[9] = 509;
		p1[10] = 508;
		break;
	}

	compute_intercept_slope(priv, p1, p2, mode);
	kfree(calib);
	kfree(bkp);

	return 0;
}