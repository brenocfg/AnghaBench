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
typedef  int int8 ;
typedef  scalar_t__ int16 ;
typedef  int /*<<< orphan*/  float64 ;
typedef  int /*<<< orphan*/  flag ;
typedef  int bits64 ;

/* Variables and functions */
 int countLeadingZeros64 (int) ; 
 int /*<<< orphan*/  roundAndPackFloat64 (struct roundingData*,int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static float64
 normalizeRoundAndPackFloat64( struct roundingData *roundData, flag zSign, int16 zExp, bits64 zSig )
{
    int8 shiftCount;

    shiftCount = countLeadingZeros64( zSig ) - 1;
    return roundAndPackFloat64( roundData, zSign, zExp - shiftCount, zSig<<shiftCount );

}