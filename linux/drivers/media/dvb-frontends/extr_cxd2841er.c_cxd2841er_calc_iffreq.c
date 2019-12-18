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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  SONY_XTAL_20500 ; 
 int /*<<< orphan*/  cxd2841er_calc_iffreq_xtal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 cxd2841er_calc_iffreq(u32 ifhz)
{
	return cxd2841er_calc_iffreq_xtal(SONY_XTAL_20500, ifhz);
}