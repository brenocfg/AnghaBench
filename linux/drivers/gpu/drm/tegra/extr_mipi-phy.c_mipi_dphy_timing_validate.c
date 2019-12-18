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
struct mipi_dphy_timing {int clkmiss; int clkpost; int clkpre; int clkprepare; int clksettle; int clktermen; int clktrail; int clkzero; int dtermen; int eot; int hsexit; int hsprepare; int hszero; int hssettle; int hsskip; scalar_t__ hstrail; int init; int lpx; int taget; int tago; int tasure; int wakeup; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ max (int,int) ; 

int mipi_dphy_timing_validate(struct mipi_dphy_timing *timing,
			      unsigned long period)
{
	if (timing->clkmiss > 60)
		return -EINVAL;

	if (timing->clkpost < (60 + 52 * period))
		return -EINVAL;

	if (timing->clkpre < 8)
		return -EINVAL;

	if (timing->clkprepare < 38 || timing->clkprepare > 95)
		return -EINVAL;

	if (timing->clksettle < 95 || timing->clksettle > 300)
		return -EINVAL;

	if (timing->clktermen > 38)
		return -EINVAL;

	if (timing->clktrail < 60)
		return -EINVAL;

	if (timing->clkprepare + timing->clkzero < 300)
		return -EINVAL;

	if (timing->dtermen > 35 + 4 * period)
		return -EINVAL;

	if (timing->eot > 105 + 12 * period)
		return -EINVAL;

	if (timing->hsexit < 100)
		return -EINVAL;

	if (timing->hsprepare < 40 + 4 * period ||
	    timing->hsprepare > 85 + 6 * period)
		return -EINVAL;

	if (timing->hsprepare + timing->hszero < 145 + 10 * period)
		return -EINVAL;

	if ((timing->hssettle < 85 + 6 * period) ||
	    (timing->hssettle > 145 + 10 * period))
		return -EINVAL;

	if (timing->hsskip < 40 || timing->hsskip > 55 + 4 * period)
		return -EINVAL;

	if (timing->hstrail < max(8 * period, 60 + 4 * period))
		return -EINVAL;

	if (timing->init < 100000)
		return -EINVAL;

	if (timing->lpx < 50)
		return -EINVAL;

	if (timing->taget != 5 * timing->lpx)
		return -EINVAL;

	if (timing->tago != 4 * timing->lpx)
		return -EINVAL;

	if (timing->tasure < timing->lpx || timing->tasure > 2 * timing->lpx)
		return -EINVAL;

	if (timing->wakeup < 1000000)
		return -EINVAL;

	return 0;
}