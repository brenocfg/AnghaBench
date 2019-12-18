#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int max_mah_design; } ;
struct ab8500_fg {TYPE_1__ bat_cap; } ;

/* Variables and functions */

__attribute__((used)) static int ab8500_fg_convert_permille_to_mah(struct ab8500_fg *di, int cap_pm)
{
	return cap_pm * di->bat_cap.max_mah_design / 1000;
}