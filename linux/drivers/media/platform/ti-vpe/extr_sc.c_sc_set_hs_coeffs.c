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
typedef  int /*<<< orphan*/  u16 ;
struct sc_data {int load_coeff_h; } ;

/* Variables and functions */
 int HS_LE_16_16_SCALE ; 
 int HS_LT_9_16_SCALE ; 
 int HS_UP_SCALE ; 
 int SC_H_NUM_TAPS ; 
 int SC_NUM_PHASES ; 
 int SC_NUM_TAPS_MEM_ALIGN ; 
 int /*<<< orphan*/ ** scaler_hs_coeffs ; 

void sc_set_hs_coeffs(struct sc_data *sc, void *addr, unsigned int src_w,
		unsigned int dst_w)
{
	int sixteenths;
	int idx;
	int i, j;
	u16 *coeff_h = addr;
	const u16 *cp;

	if (dst_w > src_w) {
		idx = HS_UP_SCALE;
	} else {
		if ((dst_w << 1) < src_w)
			dst_w <<= 1;	/* first level decimation */
		if ((dst_w << 1) < src_w)
			dst_w <<= 1;	/* second level decimation */

		if (dst_w == src_w) {
			idx = HS_LE_16_16_SCALE;
		} else {
			sixteenths = (dst_w << 4) / src_w;
			if (sixteenths < 8)
				sixteenths = 8;
			idx = HS_LT_9_16_SCALE + sixteenths - 8;
		}
	}

	cp = scaler_hs_coeffs[idx];

	for (i = 0; i < SC_NUM_PHASES * 2; i++) {
		for (j = 0; j < SC_H_NUM_TAPS; j++)
			*coeff_h++ = *cp++;
		/*
		 * for each phase, the scaler expects space for 8 coefficients
		 * in it's memory. For the horizontal scaler, we copy the first
		 * 7 coefficients and skip the last slot to move to the next
		 * row to hold coefficients for the next phase
		 */
		coeff_h += SC_NUM_TAPS_MEM_ALIGN - SC_H_NUM_TAPS;
	}

	sc->load_coeff_h = true;
}