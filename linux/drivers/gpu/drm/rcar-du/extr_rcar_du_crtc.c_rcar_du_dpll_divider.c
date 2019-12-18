#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rcar_du_crtc {TYPE_1__* dev; } ;
struct dpll_info {unsigned int n; unsigned int m; unsigned int fdpll; unsigned long output; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned long abs (long) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned long,unsigned int,unsigned int,unsigned int,unsigned long) ; 

__attribute__((used)) static void rcar_du_dpll_divider(struct rcar_du_crtc *rcrtc,
				 struct dpll_info *dpll,
				 unsigned long input,
				 unsigned long target)
{
	unsigned long best_diff = (unsigned long)-1;
	unsigned long diff;
	unsigned int fdpll;
	unsigned int m;
	unsigned int n;

	/*
	 *   fin                                 fvco        fout       fclkout
	 * in --> [1/M] --> |PD| -> [LPF] -> [VCO] -> [1/P] -+-> [1/FDPLL] -> out
	 *              +-> |  |                             |
	 *              |                                    |
	 *              +---------------- [1/N] <------------+
	 *
	 *	fclkout = fvco / P / FDPLL -- (1)
	 *
	 * fin/M = fvco/P/N
	 *
	 *	fvco = fin * P *  N / M -- (2)
	 *
	 * (1) + (2) indicates
	 *
	 *	fclkout = fin * N / M / FDPLL
	 *
	 * NOTES
	 *	N	: (n + 1)
	 *	M	: (m + 1)
	 *	FDPLL	: (fdpll + 1)
	 *	P	: 2
	 *	2kHz < fvco < 4096MHz
	 *
	 * To minimize the jitter,
	 * N : as large as possible
	 * M : as small as possible
	 */
	for (m = 0; m < 4; m++) {
		for (n = 119; n > 38; n--) {
			/*
			 * This code only runs on 64-bit architectures, the
			 * unsigned long type can thus be used for 64-bit
			 * computation. It will still compile without any
			 * warning on 32-bit architectures.
			 *
			 * To optimize calculations, use fout instead of fvco
			 * to verify the VCO frequency constraint.
			 */
			unsigned long fout = input * (n + 1) / (m + 1);

			if (fout < 1000 || fout > 2048 * 1000 * 1000U)
				continue;

			for (fdpll = 1; fdpll < 32; fdpll++) {
				unsigned long output;

				output = fout / (fdpll + 1);
				if (output >= 400 * 1000 * 1000)
					continue;

				diff = abs((long)output - (long)target);
				if (best_diff > diff) {
					best_diff = diff;
					dpll->n = n;
					dpll->m = m;
					dpll->fdpll = fdpll;
					dpll->output = output;
				}

				if (diff == 0)
					goto done;
			}
		}
	}

done:
	dev_dbg(rcrtc->dev->dev,
		"output:%u, fdpll:%u, n:%u, m:%u, diff:%lu\n",
		 dpll->output, dpll->fdpll, dpll->n, dpll->m, best_diff);
}