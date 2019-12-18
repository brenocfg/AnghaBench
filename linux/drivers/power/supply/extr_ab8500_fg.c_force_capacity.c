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
struct TYPE_2__ {int user_mah; int max_mah_design; int mah; int /*<<< orphan*/  permille; } ;
struct ab8500_fg {TYPE_1__ bat_cap; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ab8500_fg_check_capacity_limits (struct ab8500_fg*,int) ; 
 int /*<<< orphan*/  ab8500_fg_clear_cap_samples (struct ab8500_fg*) ; 
 int /*<<< orphan*/  ab8500_fg_convert_mah_to_permille (struct ab8500_fg*,int) ; 
 int /*<<< orphan*/  ab8500_fg_fill_cap_sample (struct ab8500_fg*,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static void force_capacity(struct ab8500_fg *di)
{
	int cap;

	ab8500_fg_clear_cap_samples(di);
	cap = di->bat_cap.user_mah;
	if (cap > di->bat_cap.max_mah_design) {
		dev_dbg(di->dev, "Remaining cap %d can't be bigger than total"
			" %d\n", cap, di->bat_cap.max_mah_design);
		cap = di->bat_cap.max_mah_design;
	}
	ab8500_fg_fill_cap_sample(di, di->bat_cap.user_mah);
	di->bat_cap.permille = ab8500_fg_convert_mah_to_permille(di, cap);
	di->bat_cap.mah = cap;
	ab8500_fg_check_capacity_limits(di, true);
}