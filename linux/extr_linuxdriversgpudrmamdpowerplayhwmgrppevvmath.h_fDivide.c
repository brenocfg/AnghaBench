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
typedef  int int64_t ;
struct TYPE_8__ {int full; } ;
typedef  TYPE_1__ fInt ;

/* Variables and functions */
 TYPE_1__ ConvertToFraction (int /*<<< orphan*/ ) ; 
 scalar_t__ Equal (TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  div64_s64 (int,int) ; 

__attribute__((used)) static fInt fDivide (fInt X, fInt Y)
{
	fInt fZERO, fQuotient;
	int64_t longlongX, longlongY;

	fZERO = ConvertToFraction(0);

	if (Equal(Y, fZERO))
		return fZERO;

	longlongX = (int64_t)X.full;
	longlongY = (int64_t)Y.full;

	longlongX = longlongX << 16; /*Q(16,16) -> Q(32,32) */

	div64_s64(longlongX, longlongY); /*Q(32,32) divided by Q(16,16) = Q(16,16) Back to original format */

	fQuotient.full = (int)longlongX;
	return fQuotient;
}