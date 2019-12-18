#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ intval; } ;
struct find_bat_param {scalar_t__ max_charge; scalar_t__ max_energy; TYPE_4__ full; TYPE_2__* bat; TYPE_2__* max_energy_bat; TYPE_2__* max_charge_bat; TYPE_2__* main; } ;
struct device {int dummy; } ;
struct TYPE_6__ {TYPE_1__* desc; } ;
struct TYPE_5__ {scalar_t__ use_for_apm; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHARGE_FULL ; 
 int /*<<< orphan*/  CHARGE_FULL_DESIGN ; 
 int /*<<< orphan*/  ENERGY_FULL ; 
 int /*<<< orphan*/  ENERGY_FULL_DESIGN ; 
 int /*<<< orphan*/  PSY_PROP (TYPE_2__*,int /*<<< orphan*/ ,TYPE_4__*) ; 
 TYPE_2__* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static int __find_main_battery(struct device *dev, void *data)
{
	struct find_bat_param *bp = (struct find_bat_param *)data;

	bp->bat = dev_get_drvdata(dev);

	if (bp->bat->desc->use_for_apm) {
		/* nice, we explicitly asked to report this battery. */
		bp->main = bp->bat;
		return 1;
	}

	if (!PSY_PROP(bp->bat, CHARGE_FULL_DESIGN, &bp->full) ||
			!PSY_PROP(bp->bat, CHARGE_FULL, &bp->full)) {
		if (bp->full.intval > bp->max_charge) {
			bp->max_charge_bat = bp->bat;
			bp->max_charge = bp->full.intval;
		}
	} else if (!PSY_PROP(bp->bat, ENERGY_FULL_DESIGN, &bp->full) ||
			!PSY_PROP(bp->bat, ENERGY_FULL, &bp->full)) {
		if (bp->full.intval > bp->max_energy) {
			bp->max_energy_bat = bp->bat;
			bp->max_energy = bp->full.intval;
		}
	}
	return 0;
}