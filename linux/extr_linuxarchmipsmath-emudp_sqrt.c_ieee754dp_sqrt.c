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
union ieee754dp {int bits; int bexp; } ;
typedef  int u64 ;
struct _ieee754_csr {int mx; int sx; int rm; int cx; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMPXDP ; 
 int /*<<< orphan*/  DPDNORMX ; 
 scalar_t__ DP_EBIAS ; 
 int DP_HIDDEN_BIT ; 
 int /*<<< orphan*/  EXPLODEXDP ; 
 int /*<<< orphan*/  FLUSHXDP ; 
#define  FPU_CSR_RN 135 
#define  FPU_CSR_RU 134 
 int FPU_CSR_RZ ; 
#define  IEEE754_CLASS_DNORM 133 
#define  IEEE754_CLASS_INF 132 
#define  IEEE754_CLASS_NORM 131 
#define  IEEE754_CLASS_QNAN 130 
#define  IEEE754_CLASS_SNAN 129 
#define  IEEE754_CLASS_ZERO 128 
 int IEEE754_INEXACT ; 
 int /*<<< orphan*/  IEEE754_INVALID_OPERATION ; 
 union ieee754dp builddp (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  ieee754_clearcx () ; 
 struct _ieee754_csr ieee754_csr ; 
 int /*<<< orphan*/  ieee754_setcx (int /*<<< orphan*/ ) ; 
 union ieee754dp ieee754dp_add (union ieee754dp,union ieee754dp) ; 
 union ieee754dp ieee754dp_div (union ieee754dp,union ieee754dp) ; 
 union ieee754dp ieee754dp_indef () ; 
 union ieee754dp ieee754dp_mul (union ieee754dp,union ieee754dp) ; 
 union ieee754dp ieee754dp_nanxcpt (union ieee754dp) ; 
 union ieee754dp ieee754dp_sub (union ieee754dp,union ieee754dp) ; 
 unsigned int* table ; 
 int xc ; 
 int xe ; 
 int xm ; 
 int /*<<< orphan*/  xs ; 

union ieee754dp ieee754dp_sqrt(union ieee754dp x)
{
	struct _ieee754_csr oldcsr;
	union ieee754dp y, z, t;
	unsigned int scalx, yh;
	COMPXDP;

	EXPLODEXDP;
	ieee754_clearcx();
	FLUSHXDP;

	/* x == INF or NAN? */
	switch (xc) {
	case IEEE754_CLASS_SNAN:
		return ieee754dp_nanxcpt(x);

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
			return ieee754dp_indef();
		}
		/* sqrt(+Inf) = Inf */
		return x;

	case IEEE754_CLASS_DNORM:
		DPDNORMX;
		/* fall through */

	case IEEE754_CLASS_NORM:
		if (xs) {
			/* sqrt(-x) = Nan */
			ieee754_setcx(IEEE754_INVALID_OPERATION);
			return ieee754dp_indef();
		}
		break;
	}

	/* save old csr; switch off INX enable & flag; set RN rounding */
	oldcsr = ieee754_csr;
	ieee754_csr.mx &= ~IEEE754_INEXACT;
	ieee754_csr.sx &= ~IEEE754_INEXACT;
	ieee754_csr.rm = FPU_CSR_RN;

	/* adjust exponent to prevent overflow */
	scalx = 0;
	if (xe > 512) {		/* x > 2**-512? */
		xe -= 512;	/* x = x / 2**512 */
		scalx += 256;
	} else if (xe < -512) { /* x < 2**-512? */
		xe += 512;	/* x = x * 2**512 */
		scalx -= 256;
	}

	x = builddp(0, xe + DP_EBIAS, xm & ~DP_HIDDEN_BIT);
	y = x;

	/* magic initial approximation to almost 8 sig. bits */
	yh = y.bits >> 32;
	yh = (yh >> 1) + 0x1ff80000;
	yh = yh - table[(yh >> 15) & 31];
	y.bits = ((u64) yh << 32) | (y.bits & 0xffffffff);

	/* Heron's rule once with correction to improve to ~18 sig. bits */
	/* t=x/y; y=y+t; py[n0]=py[n0]-0x00100006; py[n1]=0; */
	t = ieee754dp_div(x, y);
	y = ieee754dp_add(y, t);
	y.bits -= 0x0010000600000000LL;
	y.bits &= 0xffffffff00000000LL;

	/* triple to almost 56 sig. bits: y ~= sqrt(x) to within 1 ulp */
	/* t=y*y; z=t;	pt[n0]+=0x00100000; t+=z; z=(x-z)*y; */
	t = ieee754dp_mul(y, y);
	z = t;
	t.bexp += 0x001;
	t = ieee754dp_add(t, z);
	z = ieee754dp_mul(ieee754dp_sub(x, z), y);

	/* t=z/(t+x) ;	pt[n0]+=0x00100000; y+=t; */
	t = ieee754dp_div(z, ieee754dp_add(t, x));
	t.bexp += 0x001;
	y = ieee754dp_add(y, t);

	/* twiddle last bit to force y correctly rounded */

	/* set RZ, clear INEX flag */
	ieee754_csr.rm = FPU_CSR_RZ;
	ieee754_csr.sx &= ~IEEE754_INEXACT;

	/* t=x/y; ...chopped quotient, possibly inexact */
	t = ieee754dp_div(x, y);

	if (ieee754_csr.sx & IEEE754_INEXACT || t.bits != y.bits) {

		if (!(ieee754_csr.sx & IEEE754_INEXACT))
			/* t = t-ulp */
			t.bits -= 1;

		/* add inexact to result status */
		oldcsr.cx |= IEEE754_INEXACT;
		oldcsr.sx |= IEEE754_INEXACT;

		switch (oldcsr.rm) {
		case FPU_CSR_RU:
			y.bits += 1;
			/* fall through */
		case FPU_CSR_RN:
			t.bits += 1;
			break;
		}

		/* y=y+t; ...chopped sum */
		y = ieee754dp_add(y, t);

		/* adjust scalx for correctly rounded sqrt(x) */
		scalx -= 1;
	}

	/* py[n0]=py[n0]+scalx; ...scale back y */
	y.bexp += scalx;

	/* restore rounding mode, possibly set inexact */
	ieee754_csr = oldcsr;

	return y;
}