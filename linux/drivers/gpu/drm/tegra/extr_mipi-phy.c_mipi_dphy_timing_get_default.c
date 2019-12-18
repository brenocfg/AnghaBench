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
struct mipi_dphy_timing {int clkpost; int clkpre; int clkprepare; int clksettle; int clktrail; int clkzero; int hsexit; int hsprepare; int hszero; int hssettle; int hsskip; int init; int lpx; int taget; int tago; int tasure; int wakeup; int /*<<< orphan*/  hstrail; scalar_t__ eot; scalar_t__ dtermen; scalar_t__ clktermen; scalar_t__ clkmiss; } ;

/* Variables and functions */
 int /*<<< orphan*/  max (int,int) ; 

int mipi_dphy_timing_get_default(struct mipi_dphy_timing *timing,
				 unsigned long period)
{
	timing->clkmiss = 0;
	timing->clkpost = 70 + 52 * period;
	timing->clkpre = 8;
	timing->clkprepare = 65;
	timing->clksettle = 95;
	timing->clktermen = 0;
	timing->clktrail = 80;
	timing->clkzero = 260;
	timing->dtermen = 0;
	timing->eot = 0;
	timing->hsexit = 120;
	timing->hsprepare = 65 + 5 * period;
	timing->hszero = 145 + 5 * period;
	timing->hssettle = 85 + 6 * period;
	timing->hsskip = 40;

	/*
	 * The MIPI D-PHY specification (Section 6.9, v1.2, Table 14, Page 40)
	 * contains this formula as:
	 *
	 *     T_HS-TRAIL = max(n * 8 * period, 60 + n * 4 * period)
	 *
	 * where n = 1 for forward-direction HS mode and n = 4 for reverse-
	 * direction HS mode. There's only one setting and this function does
	 * not parameterize on anything other that period, so this code will
	 * assumes that reverse-direction HS mode is supported and uses n = 4.
	 */
	timing->hstrail = max(4 * 8 * period, 60 + 4 * 4 * period);

	timing->init = 100000;
	timing->lpx = 60;
	timing->taget = 5 * timing->lpx;
	timing->tago = 4 * timing->lpx;
	timing->tasure = 2 * timing->lpx;
	timing->wakeup = 1000000;

	return 0;
}