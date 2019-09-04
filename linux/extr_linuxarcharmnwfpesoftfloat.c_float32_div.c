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
typedef  int int16 ;
typedef  int /*<<< orphan*/  float32 ;
typedef  int flag ;
typedef  int bits64 ;
typedef  int bits32 ;

/* Variables and functions */
 int /*<<< orphan*/  do_div (int,int) ; 
 int extractFloat32Exp (int /*<<< orphan*/ ) ; 
 int extractFloat32Frac (int /*<<< orphan*/ ) ; 
 int extractFloat32Sign (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  float32_default_nan ; 
 int /*<<< orphan*/  float_flag_divbyzero ; 
 int /*<<< orphan*/  float_flag_invalid ; 
 int /*<<< orphan*/  normalizeFloat32Subnormal (int,int*,int*) ; 
 int /*<<< orphan*/  packFloat32 (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  propagateFloat32NaN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  roundAndPackFloat32 (struct roundingData*,int,int,int) ; 

float32 float32_div( struct roundingData *roundData, float32 a, float32 b )
{
    flag aSign, bSign, zSign;
    int16 aExp, bExp, zExp;
    bits32 aSig, bSig, zSig;

    aSig = extractFloat32Frac( a );
    aExp = extractFloat32Exp( a );
    aSign = extractFloat32Sign( a );
    bSig = extractFloat32Frac( b );
    bExp = extractFloat32Exp( b );
    bSign = extractFloat32Sign( b );
    zSign = aSign ^ bSign;
    if ( aExp == 0xFF ) {
        if ( aSig ) return propagateFloat32NaN( a, b );
        if ( bExp == 0xFF ) {
            if ( bSig ) return propagateFloat32NaN( a, b );
            roundData->exception |= float_flag_invalid;
            return float32_default_nan;
        }
        return packFloat32( zSign, 0xFF, 0 );
    }
    if ( bExp == 0xFF ) {
        if ( bSig ) return propagateFloat32NaN( a, b );
        return packFloat32( zSign, 0, 0 );
    }
    if ( bExp == 0 ) {
        if ( bSig == 0 ) {
            if ( ( aExp | aSig ) == 0 ) {
                roundData->exception |= float_flag_invalid;
                return float32_default_nan;
            }
            roundData->exception |= float_flag_divbyzero;
            return packFloat32( zSign, 0xFF, 0 );
        }
        normalizeFloat32Subnormal( bSig, &bExp, &bSig );
    }
    if ( aExp == 0 ) {
        if ( aSig == 0 ) return packFloat32( zSign, 0, 0 );
        normalizeFloat32Subnormal( aSig, &aExp, &aSig );
    }
    zExp = aExp - bExp + 0x7D;
    aSig = ( aSig | 0x00800000 )<<7;
    bSig = ( bSig | 0x00800000 )<<8;
    if ( bSig <= ( aSig + aSig ) ) {
        aSig >>= 1;
        ++zExp;
    }
    {
        bits64 tmp = ( (bits64) aSig )<<32;
        do_div( tmp, bSig );
        zSig = tmp;
    }
    if ( ( zSig & 0x3F ) == 0 ) {
        zSig |= ( ( (bits64) bSig ) * zSig != ( (bits64) aSig )<<32 );
    }
    return roundAndPackFloat32( roundData, zSign, zExp, zSig );

}