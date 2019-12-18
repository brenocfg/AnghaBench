#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int decimal; } ;
struct TYPE_5__ {TYPE_1__ partial; } ;
typedef  TYPE_2__ fInt ;

/* Variables and functions */
 int PRECISION ; 
 int SHIFT_AMOUNT ; 
 int uPow (int,int) ; 

__attribute__((used)) static int uGetScaledDecimal (fInt A) /*Converts the fractional portion to whole integers - Costly function */
{
	int dec[PRECISION];
	int i, scaledDecimal = 0, tmp = A.partial.decimal;

	for (i = 0; i < PRECISION; i++) {
		dec[i] = tmp / (1 << SHIFT_AMOUNT);
		tmp = tmp - ((1 << SHIFT_AMOUNT)*dec[i]);
		tmp *= 10;
		scaledDecimal = scaledDecimal + dec[i]*uPow(10, PRECISION - 1 -i);
	}

	return scaledDecimal;
}