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
union ieee754sp {int bits; } ;
struct TYPE_2__ {int rm; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMPXSP ; 
 int /*<<< orphan*/  EXPLODEXSP ; 
 int /*<<< orphan*/  FLUSHXSP ; 
#define  FPU_CSR_RN 135 
#define  FPU_CSR_RU 134 
#define  IEEE754_CLASS_DNORM 133 
#define  IEEE754_CLASS_INF 132 
#define  IEEE754_CLASS_NORM 131 
#define  IEEE754_CLASS_QNAN 130 
#define  IEEE754_CLASS_SNAN 129 
#define  IEEE754_CLASS_ZERO 128 
 int /*<<< orphan*/  IEEE754_INEXACT ; 
 int /*<<< orphan*/  IEEE754_INVALID_OPERATION ; 
 int /*<<< orphan*/  ieee754_clearcx () ; 
 TYPE_1__ ieee754_csr ; 
 int /*<<< orphan*/  ieee754_setcx (int /*<<< orphan*/ ) ; 
 union ieee754sp ieee754sp_indef () ; 
 union ieee754sp ieee754sp_nanxcpt (union ieee754sp) ; 
 int xc ; 
 int /*<<< orphan*/  xs ; 

union ieee754sp ieee754sp_sqrt(union ieee754sp x)
{
	int ix, s, q, m, t, i;
	unsigned int r;
	COMPXSP;

	/* take care of Inf and NaN */

	EXPLODEXSP;
	ieee754_clearcx();
	FLUSHXSP;

	/* x == INF or NAN? */
	switch (xc) {
	case IEEE754_CLASS_SNAN:
		return ieee754sp_nanxcpt(x);

	case IEEE754_CLASS_QNAN:
		/* sqrt(Nan) = Nan */
		return x;

	case IEEE754_CLASS_ZERO:
		/* sqrt(0) = 0 */
		return x;

	case IEEE754_CLASS_INF:
		if (xs) {
			/* sqrt(-Inf) = Nan */
			ieee754_setcx(IEEE754_INVALID_OPERATION);
			return ieee754sp_indef();
		}
		/* sqrt(+Inf) = Inf */
		return x;

	case IEEE754_CLASS_DNORM:
	case IEEE754_CLASS_NORM:
		if (xs) {
			/* sqrt(-x) = Nan */
			ieee754_setcx(IEEE754_INVALID_OPERATION);
			return ieee754sp_indef();
		}
		break;
	}

	ix = x.bits;

	/* normalize x */
	m = (ix >> 23);
	if (m == 0) {		/* subnormal x */
		for (i = 0; (ix & 0x00800000) == 0; i++)
			ix <<= 1;
		m -= i - 1;
	}
	m -= 127;		/* unbias exponent */
	ix = (ix & 0x007fffff) | 0x00800000;
	if (m & 1)		/* odd m, double x to make it even */
		ix += ix;
	m >>= 1;		/* m = [m/2] */

	/* generate sqrt(x) bit by bit */
	ix += ix;
	s = 0;
	q = 0;			/* q = sqrt(x) */
	r = 0x01000000;		/* r = moving bit from right to left */

	while (r != 0) {
		t = s + r;
		if (t <= ix) {
			s = t + r;
			ix -= t;
			q += r;
		}
		ix += ix;
		r >>= 1;
	}

	if (ix != 0) {
		ieee754_setcx(IEEE754_INEXACT);
		switch (ieee754_csr.rm) {
		case FPU_CSR_RU:
			q += 2;
			break;
		case FPU_CSR_RN:
			q += (q & 1);
			break;
		}
	}
	ix = (q >> 1) + 0x3f000000;
	ix += (m << 23);
	x.bits = ix;
	return x;
}