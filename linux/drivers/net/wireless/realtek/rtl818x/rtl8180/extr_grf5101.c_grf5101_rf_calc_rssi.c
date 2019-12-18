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

__attribute__((used)) static u8 grf5101_rf_calc_rssi(u8 agc, u8 sq)
{
	if (agc > 60)
		return 65;

	/* TODO(?): just return agc (or agc + 5) to avoid mult / div */
	return 65 * agc / 60;
}