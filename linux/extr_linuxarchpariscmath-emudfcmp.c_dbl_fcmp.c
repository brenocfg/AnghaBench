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
typedef  int /*<<< orphan*/  dbl_floating_point ;

/* Variables and functions */
 scalar_t__ DBL_INFINITY_EXPONENT ; 
 scalar_t__ Dbl_allp1 (unsigned int) ; 
 scalar_t__ Dbl_allp2 (unsigned int) ; 
 int /*<<< orphan*/  Dbl_copyfromptr (int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 scalar_t__ Dbl_exponent (unsigned int) ; 
 scalar_t__ Dbl_isequal (unsigned int,unsigned int,unsigned int,unsigned int) ; 
 scalar_t__ Dbl_isnotzero_mantissa (unsigned int,unsigned int) ; 
 scalar_t__ Dbl_isone_sign (unsigned int) ; 
 scalar_t__ Dbl_isone_signaling (unsigned int) ; 
 scalar_t__ Dbl_iszero_exponentmantissa (unsigned int,unsigned int) ; 
 scalar_t__ Dbl_iszero_sign (unsigned int) ; 
 int /*<<< orphan*/  Dbl_xortointp1 (unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  Equal (unsigned int) ; 
 scalar_t__ Exception (unsigned int) ; 
 int /*<<< orphan*/  Greaterthan (unsigned int) ; 
 int INVALIDEXCEPTION ; 
 scalar_t__ Is_invalidtrap_enabled () ; 
 int /*<<< orphan*/  Lessthan (unsigned int) ; 
 int NOEXCEPTION ; 
 int /*<<< orphan*/  Set_invalidflag () ; 
 int /*<<< orphan*/  Set_status_cbit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unordered (unsigned int) ; 

int
dbl_fcmp (dbl_floating_point * leftptr, dbl_floating_point * rightptr,
	  unsigned int cond, unsigned int *status)
                                           
                       /* The predicate to be tested */
                         
    {
    register unsigned int leftp1, leftp2, rightp1, rightp2;
    register int xorresult;
        
    /* Create local copies of the numbers */
    Dbl_copyfromptr(leftptr,leftp1,leftp2);
    Dbl_copyfromptr(rightptr,rightp1,rightp2);
    /*
     * Test for NaN
     */
    if(    (Dbl_exponent(leftp1) == DBL_INFINITY_EXPONENT)
        || (Dbl_exponent(rightp1) == DBL_INFINITY_EXPONENT) )
	{
	/* Check if a NaN is involved.  Signal an invalid exception when 
	 * comparing a signaling NaN or when comparing quiet NaNs and the
	 * low bit of the condition is set */
        if( ((Dbl_exponent(leftp1) == DBL_INFINITY_EXPONENT)
	    && Dbl_isnotzero_mantissa(leftp1,leftp2) 
	    && (Exception(cond) || Dbl_isone_signaling(leftp1)))
	   ||
	    ((Dbl_exponent(rightp1) == DBL_INFINITY_EXPONENT)
	    && Dbl_isnotzero_mantissa(rightp1,rightp2) 
	    && (Exception(cond) || Dbl_isone_signaling(rightp1))) )
	    {
	    if( Is_invalidtrap_enabled() ) {
	    	Set_status_cbit(Unordered(cond));
		return(INVALIDEXCEPTION);
	    }
	    else Set_invalidflag();
	    Set_status_cbit(Unordered(cond));
	    return(NOEXCEPTION);
	    }
	/* All the exceptional conditions are handled, now special case
	   NaN compares */
        else if( ((Dbl_exponent(leftp1) == DBL_INFINITY_EXPONENT)
	    && Dbl_isnotzero_mantissa(leftp1,leftp2))
	   ||
	    ((Dbl_exponent(rightp1) == DBL_INFINITY_EXPONENT)
	    && Dbl_isnotzero_mantissa(rightp1,rightp2)) )
	    {
	    /* NaNs always compare unordered. */
	    Set_status_cbit(Unordered(cond));
	    return(NOEXCEPTION);
	    }
	/* infinities will drop down to the normal compare mechanisms */
	}
    /* First compare for unequal signs => less or greater or
     * special equal case */
    Dbl_xortointp1(leftp1,rightp1,xorresult);
    if( xorresult < 0 )
        {
        /* left negative => less, left positive => greater.
         * equal is possible if both operands are zeros. */
        if( Dbl_iszero_exponentmantissa(leftp1,leftp2) 
	  && Dbl_iszero_exponentmantissa(rightp1,rightp2) )
            {
	    Set_status_cbit(Equal(cond));
	    }
	else if( Dbl_isone_sign(leftp1) )
	    {
	    Set_status_cbit(Lessthan(cond));
	    }
	else
	    {
	    Set_status_cbit(Greaterthan(cond));
	    }
        }
    /* Signs are the same.  Treat negative numbers separately
     * from the positives because of the reversed sense.  */
    else if(Dbl_isequal(leftp1,leftp2,rightp1,rightp2))
        {
        Set_status_cbit(Equal(cond));
        }
    else if( Dbl_iszero_sign(leftp1) )
        {
        /* Positive compare */
	if( Dbl_allp1(leftp1) < Dbl_allp1(rightp1) )
	    {
	    Set_status_cbit(Lessthan(cond));
	    }
	else if( Dbl_allp1(leftp1) > Dbl_allp1(rightp1) )
	    {
	    Set_status_cbit(Greaterthan(cond));
	    }
	else
	    {
	    /* Equal first parts.  Now we must use unsigned compares to
	     * resolve the two possibilities. */
	    if( Dbl_allp2(leftp2) < Dbl_allp2(rightp2) )
		{
		Set_status_cbit(Lessthan(cond));
		}
	    else 
		{
		Set_status_cbit(Greaterthan(cond));
		}
	    }
	}
    else
        {
        /* Negative compare.  Signed or unsigned compares
         * both work the same.  That distinction is only
         * important when the sign bits differ. */
	if( Dbl_allp1(leftp1) > Dbl_allp1(rightp1) )
	    {
	    Set_status_cbit(Lessthan(cond));
	    }
	else if( Dbl_allp1(leftp1) < Dbl_allp1(rightp1) )
	    {
	    Set_status_cbit(Greaterthan(cond));
	    }
	else
	    {
	    /* Equal first parts.  Now we must use unsigned compares to
	     * resolve the two possibilities. */
	    if( Dbl_allp2(leftp2) > Dbl_allp2(rightp2) )
		{
		Set_status_cbit(Lessthan(cond));
		}
	    else 
		{
		Set_status_cbit(Greaterthan(cond));
		}
	    }
        }
	return(NOEXCEPTION);
    }