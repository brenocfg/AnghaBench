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
struct roundingData {int dummy; } ;
typedef  int /*<<< orphan*/  int32 ;
typedef  int int16 ;
typedef  int /*<<< orphan*/  float32 ;
typedef  scalar_t__ flag ;
typedef  int bits64 ;
typedef  int bits32 ;

/* Variables and functions */
 int extractFloat32Exp (int /*<<< orphan*/ ) ; 
 int extractFloat32Frac (int /*<<< orphan*/ ) ; 
 scalar_t__ extractFloat32Sign (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  roundAndPackInt32 (struct roundingData*,scalar_t__,int) ; 
 int /*<<< orphan*/  shift64RightJamming (int,int,int*) ; 

int32 float32_to_int32( struct roundingData *roundData, float32 a )
{
    flag aSign;
    int16 aExp, shiftCount;
    bits32 aSig;
    bits64 zSig;

    aSig = extractFloat32Frac( a );
    aExp = extractFloat32Exp( a );
    aSign = extractFloat32Sign( a );
    if ( ( aExp == 0x7FF ) && aSig ) aSign = 0;
    if ( aExp ) aSig |= 0x00800000;
    shiftCount = 0xAF - aExp;
    zSig = aSig;
    zSig <<= 32;
    if ( 0 < shiftCount ) shift64RightJamming( zSig, shiftCount, &zSig );
    return roundAndPackInt32( roundData, aSign, zSig );

}