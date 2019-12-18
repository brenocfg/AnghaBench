#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int real; scalar_t__ decimal; } ;
struct TYPE_16__ {TYPE_1__ partial; } ;
typedef  TYPE_2__ fInt ;

/* Variables and functions */
 TYPE_2__ fAdd (TYPE_2__,TYPE_2__) ; 
 TYPE_2__ fDivide (TYPE_2__,TYPE_2__) ; 
 TYPE_2__ fMultiply (TYPE_2__,TYPE_2__) ; 

__attribute__((used)) static fInt fRoundUpByStepSize(fInt A, fInt fStepSize, bool error_term)
{
	fInt solution;

	solution = fDivide(A, fStepSize);
	solution.partial.decimal = 0; /*All fractional digits changes to 0 */

	if (error_term)
		solution.partial.real += 1; /*Error term of 1 added */

	solution = fMultiply(solution, fStepSize);
	solution = fAdd(solution, fStepSize);

	return solution;
}