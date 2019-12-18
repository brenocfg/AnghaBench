#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct nvkm_subdev {TYPE_3__* device; } ;
struct TYPE_10__ {int min_freq; int max_freq; int min_inputfreq; int max_inputfreq; int min_m; int max_m; int min_n; int max_n; } ;
struct TYPE_9__ {int min_freq; int max_freq; int min_inputfreq; int max_inputfreq; int min_m; int max_m; int min_n; int max_n; } ;
struct nvbios_pll {int max_p_usable; int refclk; TYPE_5__ vco2; TYPE_4__ vco1; } ;
struct TYPE_8__ {TYPE_2__* bios; } ;
struct TYPE_6__ {int chip; } ;
struct TYPE_7__ {TYPE_1__ version; } ;

/* Variables and functions */
 int INT_MAX ; 
 int abs (int) ; 

__attribute__((used)) static int
getMNP_double(struct nvkm_subdev *subdev, struct nvbios_pll *info, int clk,
	      int *pN1, int *pM1, int *pN2, int *pM2, int *pP)
{
	/* Find M, N and P for a two stage PLL
	 *
	 * Note that some bioses (NV30+) have lookup tables of precomputed MNP
	 * values, but we're too lazy to use those atm
	 *
	 * "clk" parameter in kHz
	 * returns calculated clock
	 */
	int chip_version = subdev->device->bios->version.chip;
	int minvco1 = info->vco1.min_freq, maxvco1 = info->vco1.max_freq;
	int minvco2 = info->vco2.min_freq, maxvco2 = info->vco2.max_freq;
	int minU1 = info->vco1.min_inputfreq, minU2 = info->vco2.min_inputfreq;
	int maxU1 = info->vco1.max_inputfreq, maxU2 = info->vco2.max_inputfreq;
	int minM1 = info->vco1.min_m, maxM1 = info->vco1.max_m;
	int minN1 = info->vco1.min_n, maxN1 = info->vco1.max_n;
	int minM2 = info->vco2.min_m, maxM2 = info->vco2.max_m;
	int minN2 = info->vco2.min_n, maxN2 = info->vco2.max_n;
	int maxlog2P = info->max_p_usable;
	int crystal = info->refclk;
	bool fixedgain2 = (minM2 == maxM2 && minN2 == maxN2);
	int M1, N1, M2, N2, log2P;
	int clkP, calcclk1, calcclk2, calcclkout;
	int delta, bestdelta = INT_MAX;
	int bestclk = 0;

	int vco2 = (maxvco2 - maxvco2/200) / 2;
	for (log2P = 0; clk && log2P < maxlog2P && clk <= (vco2 >> log2P); log2P++)
		;
	clkP = clk << log2P;

	if (maxvco2 < clk + clk/200)	/* +0.5% */
		maxvco2 = clk + clk/200;

	for (M1 = minM1; M1 <= maxM1; M1++) {
		if (crystal/M1 < minU1)
			return bestclk;
		if (crystal/M1 > maxU1)
			continue;

		for (N1 = minN1; N1 <= maxN1; N1++) {
			calcclk1 = crystal * N1 / M1;
			if (calcclk1 < minvco1)
				continue;
			if (calcclk1 > maxvco1)
				break;

			for (M2 = minM2; M2 <= maxM2; M2++) {
				if (calcclk1/M2 < minU2)
					break;
				if (calcclk1/M2 > maxU2)
					continue;

				/* add calcclk1/2 to round better */
				N2 = (clkP * M2 + calcclk1/2) / calcclk1;
				if (N2 < minN2)
					continue;
				if (N2 > maxN2)
					break;

				if (!fixedgain2) {
					if (chip_version < 0x60)
						if (N2/M2 < 4 || N2/M2 > 10)
							continue;

					calcclk2 = calcclk1 * N2 / M2;
					if (calcclk2 < minvco2)
						break;
					if (calcclk2 > maxvco2)
						continue;
				} else
					calcclk2 = calcclk1;

				calcclkout = calcclk2 >> log2P;
				delta = abs(calcclkout - clk);
				/* we do an exhaustive search rather than terminating
				 * on an optimality condition...
				 */
				if (delta < bestdelta) {
					bestdelta = delta;
					bestclk = calcclkout;
					*pN1 = N1;
					*pM1 = M1;
					*pN2 = N2;
					*pM2 = M2;
					*pP = log2P;
					if (delta == 0)	/* except this one */
						return bestclk;
				}
			}
		}
	}

	return bestclk;
}