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
typedef  union ieee754sp {int dummy; } ieee754sp ;

/* Variables and functions */
 int /*<<< orphan*/  SPXSRSX1 () ; 
 int SP_FBITS ; 
 int /*<<< orphan*/  ieee754_clearcx () ; 
 union ieee754sp ieee754sp_format (int,int,unsigned int) ; 
 union ieee754sp ieee754sp_one (int) ; 
 union ieee754sp ieee754sp_ten (int) ; 
 union ieee754sp ieee754sp_zero (int /*<<< orphan*/ ) ; 

union ieee754sp ieee754sp_fint(int x)
{
	unsigned int xm;
	int xe;
	int xs;

	ieee754_clearcx();

	if (x == 0)
		return ieee754sp_zero(0);
	if (x == 1 || x == -1)
		return ieee754sp_one(x < 0);
	if (x == 10 || x == -10)
		return ieee754sp_ten(x < 0);

	xs = (x < 0);
	if (xs) {
		if (x == (1 << 31))
			xm = ((unsigned) 1 << 31);	/* max neg can't be safely negated */
		else
			xm = -x;
	} else {
		xm = x;
	}
	xe = SP_FBITS + 3;

	if (xm >> (SP_FBITS + 1 + 3)) {
		/* shunt out overflow bits
		 */
		while (xm >> (SP_FBITS + 1 + 3)) {
			SPXSRSX1();
		}
	} else {
		/* normalize in grs extended single precision
		 */
		while ((xm >> (SP_FBITS + 3)) == 0) {
			xm <<= 1;
			xe--;
		}
	}
	return ieee754sp_format(xs, xe, xm);
}