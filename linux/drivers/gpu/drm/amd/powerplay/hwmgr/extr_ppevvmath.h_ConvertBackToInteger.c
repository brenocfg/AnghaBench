#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int full; } ;
typedef  TYPE_1__ fInt ;

/* Variables and functions */
 int GetReal (TYPE_1__) ; 
 scalar_t__ PRECISION ; 
 TYPE_1__ fAdd (TYPE_1__,TYPE_1__) ; 
 int uGetScaledDecimal (TYPE_1__) ; 
 int uPow (int,scalar_t__) ; 

__attribute__((used)) static int ConvertBackToInteger (fInt A) /*THIS is the function that will be used to check with the Golden settings table*/
{
	fInt fullNumber, scaledDecimal, scaledReal;

	scaledReal.full = GetReal(A) * uPow(10, PRECISION-1); /* DOUBLE CHECK THISSSS!!! */

	scaledDecimal.full = uGetScaledDecimal(A);

	fullNumber = fAdd(scaledDecimal,scaledReal);

	return fullNumber.full;
}