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
struct roundingData {int /*<<< orphan*/  exception; } ;
typedef  scalar_t__ sbits64 ;
typedef  int int16 ;
typedef  int /*<<< orphan*/  float64 ;
typedef  int flag ;
typedef  int bits64 ;

/* Variables and functions */
 int LIT64 (int) ; 
 int extractFloat64Exp (int /*<<< orphan*/ ) ; 
 int extractFloat64Frac (int /*<<< orphan*/ ) ; 
 int extractFloat64Sign (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  float64_default_nan ; 
 int /*<<< orphan*/  float_flag_invalid ; 
 int /*<<< orphan*/  mul64To128 (int,int,int*,int*) ; 
 int /*<<< orphan*/  normalizeFloat64Subnormal (int,int*,int*) ; 
 int /*<<< orphan*/  packFloat64 (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  propagateFloat64NaN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  roundAndPackFloat64 (struct roundingData*,int,int,int) ; 

float64 float64_mul( struct roundingData *roundData, float64 a, float64 b )
{
    flag aSign, bSign, zSign;
    int16 aExp, bExp, zExp;
    bits64 aSig, bSig, zSig0, zSig1;

    aSig = extractFloat64Frac( a );
    aExp = extractFloat64Exp( a );
    aSign = extractFloat64Sign( a );
    bSig = extractFloat64Frac( b );
    bExp = extractFloat64Exp( b );
    bSign = extractFloat64Sign( b );
    zSign = aSign ^ bSign;
    if ( aExp == 0x7FF ) {
        if ( aSig || ( ( bExp == 0x7FF ) && bSig ) ) {
            return propagateFloat64NaN( a, b );
        }
        if ( ( bExp | bSig ) == 0 ) {
            roundData->exception |= float_flag_invalid;
            return float64_default_nan;
        }
        return packFloat64( zSign, 0x7FF, 0 );
    }
    if ( bExp == 0x7FF ) {
        if ( bSig ) return propagateFloat64NaN( a, b );
        if ( ( aExp | aSig ) == 0 ) {
            roundData->exception |= float_flag_invalid;
            return float64_default_nan;
        }
        return packFloat64( zSign, 0x7FF, 0 );
    }
    if ( aExp == 0 ) {
        if ( aSig == 0 ) return packFloat64( zSign, 0, 0 );
        normalizeFloat64Subnormal( aSig, &aExp, &aSig );
    }
    if ( bExp == 0 ) {
        if ( bSig == 0 ) return packFloat64( zSign, 0, 0 );
        normalizeFloat64Subnormal( bSig, &bExp, &bSig );
    }
    zExp = aExp + bExp - 0x3FF;
    aSig = ( aSig | LIT64( 0x0010000000000000 ) )<<10;
    bSig = ( bSig | LIT64( 0x0010000000000000 ) )<<11;
    mul64To128( aSig, bSig, &zSig0, &zSig1 );
    zSig0 |= ( zSig1 != 0 );
    if ( 0 <= (sbits64) ( zSig0<<1 ) ) {
        zSig0 <<= 1;
        --zExp;
    }
    return roundAndPackFloat64( roundData, zSign, zExp, zSig0 );

}