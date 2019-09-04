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
struct dpll {int m; int m2; int p; int p1; int p2; scalar_t__ n; int vco; int dot; } ;

/* Variables and functions */
 void* DIV_ROUND_CLOSEST (int,scalar_t__) ; 
 scalar_t__ WARN_ON (int) ; 

__attribute__((used)) static int pnv_calc_dpll_params(int refclk, struct dpll *clock)
{
	clock->m = clock->m2 + 2;
	clock->p = clock->p1 * clock->p2;
	if (WARN_ON(clock->n == 0 || clock->p == 0))
		return 0;
	clock->vco = DIV_ROUND_CLOSEST(refclk * clock->m, clock->n);
	clock->dot = DIV_ROUND_CLOSEST(clock->vco, clock->p);

	return clock->dot;
}