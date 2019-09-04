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
typedef  enum radeon_family { ____Placeholder_radeon_family } radeon_family ;

/* Variables and functions */
 int CHIP_RV770 ; 
 int CHIP_TAHITI ; 

__attribute__((used)) static int radeon_gart_size_auto(enum radeon_family family)
{
	/* default to a larger gart size on newer asics */
	if (family >= CHIP_TAHITI)
		return 2048;
	else if (family >= CHIP_RV770)
		return 1024;
	else
		return 512;
}