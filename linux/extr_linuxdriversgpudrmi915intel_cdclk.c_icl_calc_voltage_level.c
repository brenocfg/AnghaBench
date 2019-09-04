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
typedef  int u8 ;

/* Variables and functions */
 int /*<<< orphan*/  MISSING_CASE (int) ; 

__attribute__((used)) static u8 icl_calc_voltage_level(int cdclk)
{
	switch (cdclk) {
	case 50000:
	case 307200:
	case 312000:
		return 0;
	case 556800:
	case 552000:
		return 1;
	default:
		MISSING_CASE(cdclk);
		/* fall through */
	case 652800:
	case 648000:
		return 2;
	}
}