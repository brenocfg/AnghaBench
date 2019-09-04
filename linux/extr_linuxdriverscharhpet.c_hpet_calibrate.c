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
struct hpets {int dummy; } ;

/* Variables and functions */
 unsigned long __hpet_calibrate (struct hpets*) ; 

__attribute__((used)) static unsigned long hpet_calibrate(struct hpets *hpetp)
{
	unsigned long ret = ~0UL;
	unsigned long tmp;

	/*
	 * Try to calibrate until return value becomes stable small value.
	 * If SMI interruption occurs in calibration loop, the return value
	 * will be big. This avoids its impact.
	 */
	for ( ; ; ) {
		tmp = __hpet_calibrate(hpetp);
		if (ret <= tmp)
			break;
		ret = tmp;
	}

	return ret;
}