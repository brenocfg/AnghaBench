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
typedef  scalar_t__ flag ;
typedef  int bits64 ;

/* Variables and functions */
 int LIT64 (int) ; 
 int /*<<< orphan*/  add128 (int,int,int,int,int*,int*) ; 
 int estimateDiv128To64 (int,int /*<<< orphan*/ ,int) ; 
 int estimateSqrt32 (int,int) ; 
 int extractFloat64Exp (int /*<<< orphan*/ ) ; 
 int extractFloat64Frac (int /*<<< orphan*/ ) ; 
 scalar_t__ extractFloat64Sign (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  float64_default_nan ; 
 int /*<<< orphan*/  float_flag_invalid ; 
 int /*<<< orphan*/  mul64To128 (int,int,int*,int*) ; 
 int /*<<< orphan*/  normalizeFloat64Subnormal (int,int*,int*) ; 
 int /*<<< orphan*/  propagateFloat64NaN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  roundAndPackFloat64 (struct roundingData*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  shift64RightJamming (int,int,int*) ; 
 int /*<<< orphan*/  shortShift128Left (int /*<<< orphan*/ ,int,int,int*,int*) ; 
 int /*<<< orphan*/  sub128 (int,int /*<<< orphan*/ ,int,int,int*,int*) ; 

float64 float64_sqrt( struct roundingData *roundData, float64 a )
{
    flag aSign;
    int16 aExp, zExp;
    bits64 aSig, zSig;
    bits64 rem0, rem1, term0, term1; //, shiftedRem;
    //float64 z;

    aSig = extractFloat64Frac( a );
    aExp = extractFloat64Exp( a );
    aSign = extractFloat64Sign( a );
    if ( aExp == 0x7FF ) {
        if ( aSig ) return propagateFloat64NaN( a, a );
        if ( ! aSign ) return a;
        roundData->exception |= float_flag_invalid;
        return float64_default_nan;
    }
    if ( aSign ) {
        if ( ( aExp | aSig ) == 0 ) return a;
        roundData->exception |= float_flag_invalid;
        return float64_default_nan;
    }
    if ( aExp == 0 ) {
        if ( aSig == 0 ) return 0;
        normalizeFloat64Subnormal( aSig, &aExp, &aSig );
    }
    zExp = ( ( aExp - 0x3FF )>>1 ) + 0x3FE;
    aSig |= LIT64( 0x0010000000000000 );
    zSig = estimateSqrt32( aExp, aSig>>21 );
    zSig <<= 31;
    aSig <<= 9 - ( aExp & 1 );
    zSig = estimateDiv128To64( aSig, 0, zSig ) + zSig + 2;
    if ( ( zSig & 0x3FF ) <= 5 ) {
        if ( zSig < 2 ) {
            zSig = LIT64( 0xFFFFFFFFFFFFFFFF );
        }
        else {
            aSig <<= 2;
            mul64To128( zSig, zSig, &term0, &term1 );
            sub128( aSig, 0, term0, term1, &rem0, &rem1 );
            while ( (sbits64) rem0 < 0 ) {
                --zSig;
                shortShift128Left( 0, zSig, 1, &term0, &term1 );
                term1 |= 1;
                add128( rem0, rem1, term0, term1, &rem0, &rem1 );
            }
            zSig |= ( ( rem0 | rem1 ) != 0 );
        }
    }
    shift64RightJamming( zSig, 1, &zSig );
    return roundAndPackFloat64( roundData, 0, zExp, zSig );

}