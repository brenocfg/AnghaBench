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
typedef  scalar_t__ int16 ;
typedef  int float32 ;
typedef  scalar_t__ flag ;
typedef  int bits32 ;

/* Variables and functions */

float32 packFloat32(flag zSign, int16 zExp, bits32 zSig)
{
	return (((bits32) zSign) << 31) + (((bits32) zExp) << 23) + zSig;
}