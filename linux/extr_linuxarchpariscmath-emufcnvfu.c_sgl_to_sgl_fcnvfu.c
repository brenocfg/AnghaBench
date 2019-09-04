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
typedef  unsigned int sgl_floating_point ;
typedef  scalar_t__ boolean ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int INEXACTEXCEPTION ; 
 int INVALIDEXCEPTION ; 
 scalar_t__ Is_inexacttrap_enabled () ; 
 scalar_t__ Is_invalidtrap_enabled () ; 
 int NOEXCEPTION ; 
#define  ROUNDMINUS 130 
#define  ROUNDNEAREST 129 
#define  ROUNDPLUS 128 
 int Rounding_mode () ; 
 int SGL_BIAS ; 
 int SGL_FX_MAX_EXP ; 
 int /*<<< orphan*/  Set_inexactflag () ; 
 int /*<<< orphan*/  Set_invalidflag () ; 
 int /*<<< orphan*/  Sgl_clear_signexponent_set_hidden (unsigned int) ; 
 int Sgl_exponent (unsigned int) ; 
 scalar_t__ Sgl_isinexact_to_unsigned (unsigned int,int) ; 
 scalar_t__ Sgl_isnotzero_exponentmantissa (unsigned int) ; 
 int /*<<< orphan*/  Sgl_isnotzero_mantissa (unsigned int) ; 
 int /*<<< orphan*/  Sgl_isone_roundbit (unsigned int,int) ; 
 scalar_t__ Sgl_isone_sign (unsigned int) ; 
 int /*<<< orphan*/  Sgl_isone_stickybit (unsigned int,int) ; 
 int /*<<< orphan*/  Sgl_iszero_sign (unsigned int) ; 
 int /*<<< orphan*/  Suint_from_sgl_mantissa (unsigned int,int,unsigned int) ; 
 scalar_t__ TRUE ; 

int
sgl_to_sgl_fcnvfu(
			sgl_floating_point *srcptr,
			unsigned int *nullptr,
			unsigned int *dstptr,
			unsigned int *status)
{
	register unsigned int src, result;
	register int src_exponent;
	register boolean inexact = FALSE;

	src = *srcptr;
	src_exponent = Sgl_exponent(src) - SGL_BIAS;

	/* 
	 * Test for overflow
	 */
	if (src_exponent > SGL_FX_MAX_EXP + 1) {
		if (Sgl_isone_sign(src)) {
			result = 0;
		} else {
			result = 0xffffffff;
		}
		if (Is_invalidtrap_enabled()) {
			return(INVALIDEXCEPTION);
		}
		Set_invalidflag();
		*dstptr = result;
		return(NOEXCEPTION);
	}
	/*
	 * Generate result
	 */
	if (src_exponent >= 0) {
		/* 
		 * Check sign.
		 * If negative, trap unimplemented.
		 */
		if (Sgl_isone_sign(src)) {
			result = 0;
			if (Is_invalidtrap_enabled()) {
				return(INVALIDEXCEPTION);
			}
			Set_invalidflag();
			*dstptr = result;
			return(NOEXCEPTION);
		}
		Sgl_clear_signexponent_set_hidden(src);
		Suint_from_sgl_mantissa(src,src_exponent,result);

		/* check for inexact */
		if (Sgl_isinexact_to_unsigned(src,src_exponent)) {
			inexact = TRUE;
			/*  round result  */
			switch (Rounding_mode()) {
			case ROUNDPLUS:
				result++;
				break;
			case ROUNDMINUS: /* never negative */
				break;
			case ROUNDNEAREST:
				if (Sgl_isone_roundbit(src,src_exponent) &&
				    (Sgl_isone_stickybit(src,src_exponent) ||
				     (result & 1))) {
			     		result++;
				}
				break;
			}
		}
	} else {
		result = 0;

		/* check for inexact */
		if (Sgl_isnotzero_exponentmantissa(src)) {
			inexact = TRUE;
			/*  round result  */
			switch (Rounding_mode()) {
			case ROUNDPLUS:
				if (Sgl_iszero_sign(src)) {
					result++;
				}
				break;
			case ROUNDMINUS:
				if (Sgl_isone_sign(src)) {
					result = 0;
					if (Is_invalidtrap_enabled()) {
						return(INVALIDEXCEPTION);
					}
					Set_invalidflag();
					inexact = FALSE;
				}
				break;
			case ROUNDNEAREST:
				if (src_exponent == -1 &&
				    Sgl_isnotzero_mantissa(src)) {
					if (Sgl_isone_sign(src)) {
						result = 0;
						if (Is_invalidtrap_enabled()) {
							return(INVALIDEXCEPTION);
						}
						Set_invalidflag();
						inexact = FALSE;
					}
			      		else result++;
				}
				break;
			}
		}
	}
	*dstptr = result;
	if (inexact) {
		if (Is_inexacttrap_enabled()) return(INEXACTEXCEPTION);
		else Set_inexactflag();
	}
	return(NOEXCEPTION);
}