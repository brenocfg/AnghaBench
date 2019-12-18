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
struct ti_lmu_bank {int dummy; } ;

/* Variables and functions */
 int ti_lmu_common_update_brightness (struct ti_lmu_bank*,int) ; 

int ti_lmu_common_set_brightness(struct ti_lmu_bank *lmu_bank, int brightness)
{
	return ti_lmu_common_update_brightness(lmu_bank, brightness);
}