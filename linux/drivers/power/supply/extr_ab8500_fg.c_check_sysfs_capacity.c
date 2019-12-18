#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int user_mah; int permille; int /*<<< orphan*/  mah; } ;
struct ab8500_fg {int /*<<< orphan*/  dev; TYPE_3__ bat_cap; TYPE_2__* bm; } ;
struct TYPE_5__ {TYPE_1__* fg_params; } ;
struct TYPE_4__ {int user_cap_limit; } ;

/* Variables and functions */
 int ab8500_fg_convert_mah_to_permille (struct ab8500_fg*,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  force_capacity (struct ab8500_fg*) ; 

__attribute__((used)) static bool check_sysfs_capacity(struct ab8500_fg *di)
{
	int cap, lower, upper;
	int cap_permille;

	cap = di->bat_cap.user_mah;

	cap_permille = ab8500_fg_convert_mah_to_permille(di,
		di->bat_cap.user_mah);

	lower = di->bat_cap.permille - di->bm->fg_params->user_cap_limit * 10;
	upper = di->bat_cap.permille + di->bm->fg_params->user_cap_limit * 10;

	if (lower < 0)
		lower = 0;
	/* 1000 is permille, -> 100 percent */
	if (upper > 1000)
		upper = 1000;

	dev_dbg(di->dev, "Capacity limits:"
		" (Lower: %d User: %d Upper: %d) [user: %d, was: %d]\n",
		lower, cap_permille, upper, cap, di->bat_cap.mah);

	/* If within limits, use the saved capacity and exit estimation...*/
	if (cap_permille > lower && cap_permille < upper) {
		dev_dbg(di->dev, "OK! Using users cap %d uAh now\n", cap);
		force_capacity(di);
		return true;
	}
	dev_dbg(di->dev, "Capacity from user out of limits, ignoring");
	return false;
}