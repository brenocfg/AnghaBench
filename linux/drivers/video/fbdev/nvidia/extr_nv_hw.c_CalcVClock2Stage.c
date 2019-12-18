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
struct nvidia_par {int CrystalFreqKHz; } ;

/* Variables and functions */

__attribute__((used)) static void CalcVClock2Stage(int clockIn,
			     int *clockOut,
			     u32 * pllOut,
			     u32 * pllBOut, struct nvidia_par *par)
{
	unsigned DeltaNew, DeltaOld;
	unsigned VClk, Freq;
	unsigned M, N, P;

	DeltaOld = 0xFFFFFFFF;

	*pllBOut = 0x80000401;	/* fixed at x4 for now */

	VClk = (unsigned)clockIn;

	for (P = 0; P <= 6; P++) {
		Freq = VClk << P;
		if ((Freq >= 400000) && (Freq <= 1000000)) {
			for (M = 1; M <= 13; M++) {
				N = ((VClk << P) * M) /
				    (par->CrystalFreqKHz << 2);
				if ((N >= 5) && (N <= 255)) {
					Freq =
					    (((par->CrystalFreqKHz << 2) * N) /
					     M) >> P;
					if (Freq > VClk)
						DeltaNew = Freq - VClk;
					else
						DeltaNew = VClk - Freq;
					if (DeltaNew < DeltaOld) {
						*pllOut =
						    (P << 16) | (N << 8) | M;
						*clockOut = Freq;
						DeltaOld = DeltaNew;
					}
				}
			}
		}
	}
}