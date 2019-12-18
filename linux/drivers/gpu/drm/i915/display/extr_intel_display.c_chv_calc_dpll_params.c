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
struct dpll {int m; int m1; int m2; int p; int p1; int p2; int n; int dot; int /*<<< orphan*/  vco; } ;

/* Variables and functions */
 int DIV_ROUND_CLOSEST (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DIV_ROUND_CLOSEST_ULL (int /*<<< orphan*/ ,int) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  mul_u32_u32 (int,int) ; 

int chv_calc_dpll_params(int refclk, struct dpll *clock)
{
	clock->m = clock->m1 * clock->m2;
	clock->p = clock->p1 * clock->p2;
	if (WARN_ON(clock->n == 0 || clock->p == 0))
		return 0;
	clock->vco = DIV_ROUND_CLOSEST_ULL(mul_u32_u32(refclk, clock->m),
					   clock->n << 22);
	clock->dot = DIV_ROUND_CLOSEST(clock->vco, clock->p);

	return clock->dot / 5;
}