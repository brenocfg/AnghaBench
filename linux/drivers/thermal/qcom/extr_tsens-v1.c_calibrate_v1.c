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
typedef  int base0 ;

/* Variables and functions */
 int BASE0_MASK ; 
 int BASE0_SHIFT ; 
 int BASE1_MASK ; 
 int BASE1_SHIFT ; 
 int CAL_SEL_MASK ; 
 int CAL_SEL_SHIFT ; 
 scalar_t__ IS_ERR (int*) ; 
#define  ONE_PT_CALIB2 129 
 int PTR_ERR (int*) ; 
 int S0_P1_MASK ; 
 int S0_P1_SHIFT ; 
 int S0_P2_MASK ; 
 int S0_P2_SHIFT ; 
 int S1_P1_MASK ; 
 int S1_P1_SHIFT ; 
 int S1_P2_MASK ; 
 int S1_P2_SHIFT ; 
 int S2_P1_MASK ; 
 int S2_P1_SHIFT ; 
 int S2_P2_MASK_1_0 ; 
 int S2_P2_MASK_5_2 ; 
 int S2_P2_SHIFT_1_0 ; 
 int S2_P2_SHIFT_5_2 ; 
 int S3_P1_MASK ; 
 int S3_P1_SHIFT ; 
 int S3_P2_MASK ; 
 int S3_P2_SHIFT ; 
 int S4_P1_MASK ; 
 int S4_P1_SHIFT ; 
 int S4_P2_MASK ; 
 int S4_P2_SHIFT ; 
 int S5_P1_MASK ; 
 int S5_P1_SHIFT ; 
 int S5_P2_MASK ; 
 int S5_P2_SHIFT ; 
 int S6_P1_MASK ; 
 int S6_P1_SHIFT ; 
 int S6_P2_MASK ; 
 int S6_P2_SHIFT ; 
 int S7_P1_MASK ; 
 int S7_P1_SHIFT ; 
 int S7_P2_MASK_1_0 ; 
 int S7_P2_MASK_5_2 ; 
 int S7_P2_SHIFT_1_0 ; 
 int S7_P2_SHIFT_5_2 ; 
 int S8_P1_MASK ; 
 int S8_P1_SHIFT ; 
 int S8_P2_MASK ; 
 int S8_P2_SHIFT ; 
 int S9_P1_MASK ; 
 int S9_P1_SHIFT ; 
 int S9_P2_MASK ; 
 int S9_P2_SHIFT ; 
#define  TWO_PT_CALIB 128 
 int /*<<< orphan*/  compute_intercept_slope (struct tsens_priv*,int*,int*,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 scalar_t__ qfprom_read (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int calibrate_v1(struct tsens_priv *priv)
{
	u32 base0 = 0, base1 = 0;
	u32 p1[10], p2[10];
	u32 mode = 0, lsb = 0, msb = 0;
	u32 *qfprom_cdata;
	int i;

	qfprom_cdata = (u32 *)qfprom_read(priv->dev, "calib");
	if (IS_ERR(qfprom_cdata))
		return PTR_ERR(qfprom_cdata);

	mode = (qfprom_cdata[4] & CAL_SEL_MASK) >> CAL_SEL_SHIFT;
	dev_dbg(priv->dev, "calibration mode is %d\n", mode);

	switch (mode) {
	case TWO_PT_CALIB:
		base1 = (qfprom_cdata[4] & BASE1_MASK) >> BASE1_SHIFT;
		p2[0] = (qfprom_cdata[0] & S0_P2_MASK) >> S0_P2_SHIFT;
		p2[1] = (qfprom_cdata[0] & S1_P2_MASK) >> S1_P2_SHIFT;
		/* This value is split over two registers, 2 bits and 4 bits */
		lsb   = (qfprom_cdata[0] & S2_P2_MASK_1_0) >> S2_P2_SHIFT_1_0;
		msb   = (qfprom_cdata[1] & S2_P2_MASK_5_2) >> S2_P2_SHIFT_5_2;
		p2[2] = msb << 2 | lsb;
		p2[3] = (qfprom_cdata[1] & S3_P2_MASK) >> S3_P2_SHIFT;
		p2[4] = (qfprom_cdata[1] & S4_P2_MASK) >> S4_P2_SHIFT;
		p2[5] = (qfprom_cdata[2] & S5_P2_MASK) >> S5_P2_SHIFT;
		p2[6] = (qfprom_cdata[2] & S6_P2_MASK) >> S6_P2_SHIFT;
		/* This value is split over two registers, 2 bits and 4 bits */
		lsb   = (qfprom_cdata[2] & S7_P2_MASK_1_0) >> S7_P2_SHIFT_1_0;
		msb   = (qfprom_cdata[3] & S7_P2_MASK_5_2) >> S7_P2_SHIFT_5_2;
		p2[7] = msb << 2 | lsb;
		p2[8] = (qfprom_cdata[3] & S8_P2_MASK) >> S8_P2_SHIFT;
		p2[9] = (qfprom_cdata[3] & S9_P2_MASK) >> S9_P2_SHIFT;
		for (i = 0; i < priv->num_sensors; i++)
			p2[i] = ((base1 + p2[i]) << 2);
		/* Fall through */
	case ONE_PT_CALIB2:
		base0 = (qfprom_cdata[4] & BASE0_MASK) >> BASE0_SHIFT;
		p1[0] = (qfprom_cdata[0] & S0_P1_MASK) >> S0_P1_SHIFT;
		p1[1] = (qfprom_cdata[0] & S1_P1_MASK) >> S1_P1_SHIFT;
		p1[2] = (qfprom_cdata[0] & S2_P1_MASK) >> S2_P1_SHIFT;
		p1[3] = (qfprom_cdata[1] & S3_P1_MASK) >> S3_P1_SHIFT;
		p1[4] = (qfprom_cdata[1] & S4_P1_MASK) >> S4_P1_SHIFT;
		p1[5] = (qfprom_cdata[2] & S5_P1_MASK) >> S5_P1_SHIFT;
		p1[6] = (qfprom_cdata[2] & S6_P1_MASK) >> S6_P1_SHIFT;
		p1[7] = (qfprom_cdata[2] & S7_P1_MASK) >> S7_P1_SHIFT;
		p1[8] = (qfprom_cdata[3] & S8_P1_MASK) >> S8_P1_SHIFT;
		p1[9] = (qfprom_cdata[3] & S9_P1_MASK) >> S9_P1_SHIFT;
		for (i = 0; i < priv->num_sensors; i++)
			p1[i] = (((base0) + p1[i]) << 2);
		break;
	default:
		for (i = 0; i < priv->num_sensors; i++) {
			p1[i] = 500;
			p2[i] = 780;
		}
		break;
	}

	compute_intercept_slope(priv, p1, p2, mode);
	kfree(qfprom_cdata);

	return 0;
}