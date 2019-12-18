#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {TYPE_1__* coeff; int /*<<< orphan*/  en; } ;
struct isif_df_csc {int start_pix; int num_pixels; int start_line; int num_lines; TYPE_2__ csc; } ;
struct TYPE_3__ {int integer; int decimal; } ;

/* Variables and functions */
 scalar_t__ CSCCTL ; 
 scalar_t__ CSCM0 ; 
 scalar_t__ FMTLNH ; 
 scalar_t__ FMTLNV ; 
 scalar_t__ FMTSLV ; 
 scalar_t__ FMTSPH ; 
 int ISIF_CSCM_MSB_SHIFT ; 
 int ISIF_CSC_COEF_INTEG_SHIFT ; 
 int ISIF_CSC_NUM_COEFF ; 
 int /*<<< orphan*/  regw (int,scalar_t__) ; 

__attribute__((used)) static void isif_config_csc(struct isif_df_csc *df_csc)
{
	u32 val1 = 0, val2 = 0, i;

	if (!df_csc->csc.en) {
		regw(0, CSCCTL);
		return;
	}
	for (i = 0; i < ISIF_CSC_NUM_COEFF; i++) {
		if ((i % 2) == 0) {
			/* CSCM - LSB */
			val1 = (df_csc->csc.coeff[i].integer <<
				ISIF_CSC_COEF_INTEG_SHIFT) |
				df_csc->csc.coeff[i].decimal;
		} else {

			/* CSCM - MSB */
			val2 = (df_csc->csc.coeff[i].integer <<
				ISIF_CSC_COEF_INTEG_SHIFT) |
				df_csc->csc.coeff[i].decimal;
			val2 <<= ISIF_CSCM_MSB_SHIFT;
			val2 |= val1;
			regw(val2, (CSCM0 + ((i - 1) << 1)));
		}
	}

	/* program the active area */
	regw(df_csc->start_pix, FMTSPH);
	/*
	 * one extra pixel as required for CSC. Actually number of
	 * pixel - 1 should be configured in this register. So we
	 * need to subtract 1 before writing to FMTSPH, but we will
	 * not do this since csc requires one extra pixel
	 */
	regw(df_csc->num_pixels, FMTLNH);
	regw(df_csc->start_line, FMTSLV);
	/*
	 * one extra line as required for CSC. See reason documented for
	 * num_pixels
	 */
	regw(df_csc->num_lines, FMTLNV);

	/* Enable CSC */
	regw(1, CSCCTL);
}