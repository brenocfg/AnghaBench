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
typedef  int /*<<< orphan*/  dbl_integer ;
typedef  int /*<<< orphan*/  dbl_floating_point ;

/* Variables and functions */
 scalar_t__ DBL_BIAS ; 
 int DBL_EXP_LENGTH ; 
 int /*<<< orphan*/  Dbl_copytoptr (unsigned int,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Dbl_increment (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  Dbl_isone_sign (unsigned int) ; 
 int /*<<< orphan*/  Dbl_iszero_sign (unsigned int) ; 
 int /*<<< orphan*/  Dbl_roundnearest_from_dint (unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  Dbl_set_exponent (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  Dbl_set_mantissap1 (unsigned int,int) ; 
 int /*<<< orphan*/  Dbl_setone_sign (unsigned int) ; 
 int /*<<< orphan*/  Dbl_setzero (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  Dbl_setzero_sign (unsigned int) ; 
 int /*<<< orphan*/  Dint_copyfromptr (int /*<<< orphan*/ *,int,unsigned int) ; 
 scalar_t__ Dint_isinexact_to_dbl (unsigned int) ; 
 int /*<<< orphan*/  Dint_negate (int,unsigned int) ; 
 int /*<<< orphan*/  Find_ms_one_bit (int,int) ; 
 int INEXACTEXCEPTION ; 
 scalar_t__ Is_inexacttrap_enabled () ; 
 int NOEXCEPTION ; 
#define  ROUNDMINUS 130 
#define  ROUNDNEAREST 129 
#define  ROUNDPLUS 128 
 int Rounding_mode () ; 
 int /*<<< orphan*/  Set_inexactflag () ; 
 int /*<<< orphan*/  Shiftdouble (int,unsigned int,int,unsigned int) ; 
 int /*<<< orphan*/  Variable_shift_double (int,unsigned int,int,int) ; 

int
dbl_to_dbl_fcnvxf(
		    dbl_integer *srcptr,
		    unsigned int *nullptr,
		    dbl_floating_point *dstptr,
		    unsigned int *status)
{
	register int srcp1, dst_exponent;
	register unsigned int srcp2, resultp1 = 0, resultp2 = 0;

	Dint_copyfromptr(srcptr,srcp1,srcp2);
	/* 
	 * set sign bit of result and get magnitude of source 
	 */
	if (srcp1 < 0) {
		Dbl_setone_sign(resultp1);
		Dint_negate(srcp1,srcp2);
	}
	else {
		Dbl_setzero_sign(resultp1);
        	/* Check for zero */
        	if (srcp1 == 0 && srcp2 ==0) {
                	Dbl_setzero(resultp1,resultp2);
                	Dbl_copytoptr(resultp1,resultp2,dstptr);
                	return(NOEXCEPTION);
		}
        }
	/*
	 * Generate exponent and normalized mantissa
	 */
	dst_exponent = 16;    /* initialize for normalization */
	if (srcp1 == 0) {
		/*
		 * Check word for most significant bit set.  Returns
		 * a value in dst_exponent indicating the bit position,
		 * between -1 and 30.
		 */
		Find_ms_one_bit(srcp2,dst_exponent);
		/*  left justify source, with msb at bit position 1  */
		if (dst_exponent >= 0) {
			srcp1 = srcp2 << dst_exponent;    
			srcp2 = 0;
		}
		else {
			srcp1 = srcp2 >> 1;
			srcp2 <<= 31;
		}
		/*
		 *  since msb set is in second word, need to 
		 *  adjust bit position count
		 */
		dst_exponent += 32;
	}
	else {
		/*
		 * Check word for most significant bit set.  Returns
		 * a value in dst_exponent indicating the bit position,
		 * between -1 and 30.
		 */
		Find_ms_one_bit(srcp1,dst_exponent);
		/*  left justify source, with msb at bit position 1  */
		if (dst_exponent > 0) {
			Variable_shift_double(srcp1,srcp2,(32-dst_exponent),
			 srcp1); 
			srcp2 <<= dst_exponent;
		}
		/*
		 * If dst_exponent = 0, we don't need to shift anything.
		 * If dst_exponent = -1, src = - 2**63 so we won't need to 
		 * shift srcp2.
		 */
		else srcp1 >>= -(dst_exponent);
	}
	Dbl_set_mantissap1(resultp1, srcp1 >> (DBL_EXP_LENGTH-1));
	Shiftdouble(srcp1,srcp2,DBL_EXP_LENGTH-1,resultp2);
	Dbl_set_exponent(resultp1, (62+DBL_BIAS) - dst_exponent);

	/* check for inexact */
	if (Dint_isinexact_to_dbl(srcp2)) {
		switch (Rounding_mode()) {
			case ROUNDPLUS: 
				if (Dbl_iszero_sign(resultp1)) {
					Dbl_increment(resultp1,resultp2);
				}
				break;
			case ROUNDMINUS: 
				if (Dbl_isone_sign(resultp1)) {
					Dbl_increment(resultp1,resultp2);
				}
				break;
			case ROUNDNEAREST:
				Dbl_roundnearest_from_dint(srcp2,resultp1,
				resultp2);
		}
		if (Is_inexacttrap_enabled()) {
			Dbl_copytoptr(resultp1,resultp2,dstptr);
			return(INEXACTEXCEPTION);
		}
		else Set_inexactflag();
	}
	Dbl_copytoptr(resultp1,resultp2,dstptr);
	return(NOEXCEPTION);
}