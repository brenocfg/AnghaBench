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
struct mrst_clock_t {int dot; int m; int p1; } ;

/* Variables and functions */

__attribute__((used)) static void mdfld_clock(int refclk, struct mrst_clock_t *clock)
{
	clock->dot = (refclk * clock->m) / clock->p1;
}