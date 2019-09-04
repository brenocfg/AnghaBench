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
typedef  scalar_t__ sbits64 ;
typedef  int int16 ;
typedef  scalar_t__ float64 ;
typedef  int flag ;
typedef  int bits64 ;
typedef  int bits16 ;

/* Variables and functions */
 int FPSCR_CAUSE_INEXACT ; 
 int FPSCR_CAUSE_OVERFLOW ; 
 int FPSCR_CAUSE_UNDERFLOW ; 
 scalar_t__ FPSCR_RM_NEAREST ; 
 int LIT64 (int) ; 
 int /*<<< orphan*/  float_raise (int) ; 
 scalar_t__ float_rounding_mode () ; 
 scalar_t__ packFloat64 (int,int,int) ; 
 int /*<<< orphan*/  shift64RightJamming (int,int,int*) ; 

__attribute__((used)) static float64 roundAndPackFloat64(flag zSign, int16 zExp, bits64 zSig)
{
	flag roundNearestEven;
	int16 roundIncrement, roundBits;
	flag isTiny;

	/* SH4 has only 2 rounding modes - round to nearest and round to zero */
	roundNearestEven = (float_rounding_mode() == FPSCR_RM_NEAREST);
	roundIncrement = 0x200;
	if (!roundNearestEven) {
		roundIncrement = 0;
	}
	roundBits = zSig & 0x3FF;
	if (0x7FD <= (bits16) zExp) {
		if ((0x7FD < zExp)
		    || ((zExp == 0x7FD)
			&& ((sbits64) (zSig + roundIncrement) < 0))
		    ) {
			float_raise(FPSCR_CAUSE_OVERFLOW | FPSCR_CAUSE_INEXACT);
			return packFloat64(zSign, 0x7FF,
					   0) - (roundIncrement == 0);
		}
		if (zExp < 0) {
			isTiny = (zExp < -1)
			    || (zSig + roundIncrement <
				LIT64(0x8000000000000000));
			shift64RightJamming(zSig, -zExp, &zSig);
			zExp = 0;
			roundBits = zSig & 0x3FF;
			if (isTiny && roundBits)
				float_raise(FPSCR_CAUSE_UNDERFLOW);
		}
	}
	if (roundBits)
		float_raise(FPSCR_CAUSE_INEXACT);
	zSig = (zSig + roundIncrement) >> 10;
	zSig &= ~(((roundBits ^ 0x200) == 0) & roundNearestEven);
	if (zSig == 0)
		zExp = 0;
	return packFloat64(zSign, zExp, zSig);

}