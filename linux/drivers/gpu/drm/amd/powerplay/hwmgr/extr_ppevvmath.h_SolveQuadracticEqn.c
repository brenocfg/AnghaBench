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
typedef  int /*<<< orphan*/  fInt ;

/* Variables and functions */
 int /*<<< orphan*/  ConvertToFraction (int) ; 
 scalar_t__ GreaterThan (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fAdd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fDivide (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fGetSquare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fMultiply (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fNegate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fSqrt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fSubtract (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void SolveQuadracticEqn(fInt A, fInt B, fInt C, fInt Roots[])
{
	fInt *pRoots = &Roots[0];
	fInt temp, root_first, root_second;
	fInt f_CONSTANT10, f_CONSTANT100;

	f_CONSTANT100 = ConvertToFraction(100);
	f_CONSTANT10 = ConvertToFraction(10);

	while(GreaterThan(A, f_CONSTANT100) || GreaterThan(B, f_CONSTANT100) || GreaterThan(C, f_CONSTANT100)) {
		A = fDivide(A, f_CONSTANT10);
		B = fDivide(B, f_CONSTANT10);
		C = fDivide(C, f_CONSTANT10);
	}

	temp = fMultiply(ConvertToFraction(4), A); /* root = 4*A */
	temp = fMultiply(temp, C); /* root = 4*A*C */
	temp = fSubtract(fGetSquare(B), temp); /* root = b^2 - 4AC */
	temp = fSqrt(temp); /*root = Sqrt (b^2 - 4AC); */

	root_first = fSubtract(fNegate(B), temp); /* b - Sqrt(b^2 - 4AC) */
	root_second = fAdd(fNegate(B), temp); /* b + Sqrt(b^2 - 4AC) */

	root_first = fDivide(root_first, ConvertToFraction(2)); /* [b +- Sqrt(b^2 - 4AC)]/[2] */
	root_first = fDivide(root_first, A); /*[b +- Sqrt(b^2 - 4AC)]/[2*A] */

	root_second = fDivide(root_second, ConvertToFraction(2)); /* [b +- Sqrt(b^2 - 4AC)]/[2] */
	root_second = fDivide(root_second, A); /*[b +- Sqrt(b^2 - 4AC)]/[2*A] */

	*(pRoots + 0) = root_first;
	*(pRoots + 1) = root_second;
}