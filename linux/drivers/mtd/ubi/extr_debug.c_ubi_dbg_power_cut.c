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
struct TYPE_2__ {int emulate_power_cut; scalar_t__ power_cut_counter; scalar_t__ power_cut_min; scalar_t__ power_cut_max; } ;
struct ubi_device {TYPE_1__ dbg; } ;

/* Variables and functions */
 unsigned int prandom_u32 () ; 
 int /*<<< orphan*/  ubi_msg (struct ubi_device*,char*) ; 
 int /*<<< orphan*/  ubi_ro_mode (struct ubi_device*) ; 

int ubi_dbg_power_cut(struct ubi_device *ubi, int caller)
{
	unsigned int range;

	if ((ubi->dbg.emulate_power_cut & caller) == 0)
		return 0;

	if (ubi->dbg.power_cut_counter == 0) {
		ubi->dbg.power_cut_counter = ubi->dbg.power_cut_min;

		if (ubi->dbg.power_cut_max > ubi->dbg.power_cut_min) {
			range = ubi->dbg.power_cut_max - ubi->dbg.power_cut_min;
			ubi->dbg.power_cut_counter += prandom_u32() % range;
		}
		return 0;
	}

	ubi->dbg.power_cut_counter--;
	if (ubi->dbg.power_cut_counter)
		return 0;

	ubi_msg(ubi, "XXXXXXXXXXXXXXX emulating a power cut XXXXXXXXXXXXXXXX");
	ubi_ro_mode(ubi);
	return 1;
}