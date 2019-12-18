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
struct sc_data {int load_coeff_v; } ;

/* Variables and functions */
 int SC_NUM_PHASES ; 
 int SC_NUM_TAPS_MEM_ALIGN ; 
 int SC_V_NUM_TAPS ; 
 int VS_1_TO_1_SCALE ; 
 int VS_LT_9_16_SCALE ; 
 int VS_UP_SCALE ; 
 int /*<<< orphan*/ ** scaler_vs_coeffs ; 

void sc_set_vs_coeffs(struct sc_data *sc, void *addr, unsigned int src_h,
		unsigned int dst_h)
{
	int sixteenths;
	int idx;
	int i, j;
	u16 *coeff_v = addr;
	const u16 *cp;

	if (dst_h > src_h) {
		idx = VS_UP_SCALE;
	} else if (dst_h == src_h) {
		idx = VS_1_TO_1_SCALE;
	} else {
		sixteenths = (dst_h << 4) / src_h;
		if (sixteenths < 8)
			sixteenths = 8;
		idx = VS_LT_9_16_SCALE + sixteenths - 8;
	}

	cp = scaler_vs_coeffs[idx];

	for (i = 0; i < SC_NUM_PHASES * 2; i++) {
		for (j = 0; j < SC_V_NUM_TAPS; j++)
			*coeff_v++ = *cp++;
		/*
		 * for the vertical scaler, we copy the first 5 coefficients and
		 * skip the last 3 slots to move to the next row to hold
		 * coefficients for the next phase
		 */
		coeff_v += SC_NUM_TAPS_MEM_ALIGN - SC_V_NUM_TAPS;
	}

	sc->load_coeff_v = true;
}