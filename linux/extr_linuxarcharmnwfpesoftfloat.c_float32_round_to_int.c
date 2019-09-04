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
struct roundingData {int mode; int /*<<< orphan*/  exception; } ;
typedef  int int8 ;
typedef  int int16 ;
typedef  int float32 ;
typedef  int flag ;
typedef  scalar_t__ bits32 ;

/* Variables and functions */
 int extractFloat32Exp (int) ; 
 scalar_t__ extractFloat32Frac (int) ; 
 int extractFloat32Sign (int) ; 
 int /*<<< orphan*/  float_flag_inexact ; 
#define  float_round_down 130 
#define  float_round_nearest_even 129 
 int float_round_to_zero ; 
#define  float_round_up 128 
 int packFloat32 (int,int,int /*<<< orphan*/ ) ; 
 int propagateFloat32NaN (int,int) ; 

float32 float32_round_to_int( struct roundingData *roundData, float32 a )
{
    flag aSign;
    int16 aExp;
    bits32 lastBitMask, roundBitsMask;
    int8 roundingMode;
    float32 z;

    aExp = extractFloat32Exp( a );
    if ( 0x96 <= aExp ) {
        if ( ( aExp == 0xFF ) && extractFloat32Frac( a ) ) {
            return propagateFloat32NaN( a, a );
        }
        return a;
    }
    roundingMode = roundData->mode;
    if ( aExp <= 0x7E ) {
        if ( (bits32) ( a<<1 ) == 0 ) return a;
        roundData->exception |= float_flag_inexact;
        aSign = extractFloat32Sign( a );
        switch ( roundingMode ) {
         case float_round_nearest_even:
            if ( ( aExp == 0x7E ) && extractFloat32Frac( a ) ) {
                return packFloat32( aSign, 0x7F, 0 );
            }
            break;
         case float_round_down:
            return aSign ? 0xBF800000 : 0;
         case float_round_up:
            return aSign ? 0x80000000 : 0x3F800000;
        }
        return packFloat32( aSign, 0, 0 );
    }
    lastBitMask = 1;
    lastBitMask <<= 0x96 - aExp;
    roundBitsMask = lastBitMask - 1;
    z = a;
    if ( roundingMode == float_round_nearest_even ) {
        z += lastBitMask>>1;
        if ( ( z & roundBitsMask ) == 0 ) z &= ~ lastBitMask;
    }
    else if ( roundingMode != float_round_to_zero ) {
        if ( extractFloat32Sign( z ) ^ ( roundingMode == float_round_up ) ) {
            z += roundBitsMask;
        }
    }
    z &= ~ roundBitsMask;
    if ( z != a ) roundData->exception |= float_flag_inexact;
    return z;

}