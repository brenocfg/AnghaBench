#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int full; } ;
typedef  TYPE_1__ fInt ;

/* Variables and functions */
 int SHIFT_AMOUNT ; 
 TYPE_1__ fDivide (TYPE_1__,TYPE_1__) ; 

__attribute__((used)) static fInt Divide (int X, int Y)
{
	fInt A, B, Quotient;

	A.full = X << SHIFT_AMOUNT;
	B.full = Y << SHIFT_AMOUNT;

	Quotient = fDivide(A, B);

	return Quotient;
}