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

/* Variables and functions */
 int /*<<< orphan*/  Find_ms_one_bit (int,int) ; 
 int INEXACTEXCEPTION ; 
 scalar_t__ Int_isinexact_to_sgl (int) ; 
 int /*<<< orphan*/  Int_negate (int) ; 
 scalar_t__ Is_inexacttrap_enabled () ; 
 int NOEXCEPTION ; 
#define  ROUNDMINUS 130 
#define  ROUNDNEAREST 129 
#define  ROUNDPLUS 128 
 int Rounding_mode () ; 
 scalar_t__ SGL_BIAS ; 
 int SGL_EXP_LENGTH ; 
 int /*<<< orphan*/  Set_inexactflag () ; 
 int /*<<< orphan*/  Sgl_increment (unsigned int) ; 
 int /*<<< orphan*/  Sgl_isone_sign (unsigned int) ; 
 int /*<<< orphan*/  Sgl_iszero_sign (unsigned int) ; 
 int /*<<< orphan*/  Sgl_roundnearest_from_int (int,unsigned int) ; 
 int /*<<< orphan*/  Sgl_set_exponent (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  Sgl_set_mantissa (unsigned int,int) ; 
 int /*<<< orphan*/  Sgl_setone_sign (unsigned int) ; 
 int /*<<< orphan*/  Sgl_setzero (unsigned int) ; 
 int /*<<< orphan*/  Sgl_setzero_sign (unsigned int) ; 

int
sgl_to_sgl_fcnvxf(
		    int *srcptr,
		    unsigned int *nullptr,
		    sgl_floating_point *dstptr,
		    unsigned int *status)
{
	register int src, dst_exponent;
	register unsigned int result = 0;

	src = *srcptr;
	/* 
	 * set sign bit of result and get magnitude of source 
	 */
	if (src < 0) {
		Sgl_setone_sign(result);  
		Int_negate(src);
	}
	else {
		Sgl_setzero_sign(result);
        	/* Check for zero */ 
        	if (src == 0) { 
                	Sgl_setzero(result); 
			*dstptr = result;
                	return(NOEXCEPTION); 
        	} 
	}
	/*
	 * Generate exponent and normalized mantissa
	 */
	dst_exponent = 16;    /* initialize for normalization */
	/*
	 * Check word for most significant bit set.  Returns
	 * a value in dst_exponent indicating the bit position,
	 * between -1 and 30.
	 */
	Find_ms_one_bit(src,dst_exponent);
	/*  left justify source, with msb at bit position 1  */
	if (dst_exponent >= 0) src <<= dst_exponent;
	else src = 1 << 30;
	Sgl_set_mantissa(result, src >> (SGL_EXP_LENGTH-1));
	Sgl_set_exponent(result, 30+SGL_BIAS - dst_exponent);

	/* check for inexact */
	if (Int_isinexact_to_sgl(src)) {
		switch (Rounding_mode()) {
			case ROUNDPLUS: 
				if (Sgl_iszero_sign(result)) 
					Sgl_increment(result);
				break;
			case ROUNDMINUS: 
				if (Sgl_isone_sign(result)) 
					Sgl_increment(result);
				break;
			case ROUNDNEAREST:
				Sgl_roundnearest_from_int(src,result);
		}
		if (Is_inexacttrap_enabled()) {
			*dstptr = result;
			return(INEXACTEXCEPTION);
		}
		else Set_inexactflag();
	}
	*dstptr = result;
	return(NOEXCEPTION);
}