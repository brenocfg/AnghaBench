#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ab8500_fg_cap_scaling {int disable_cap_level; int scaled_cap; int* cap_to_scale; int /*<<< orphan*/  enable; } ;
struct TYPE_6__ {int prev_percent; struct ab8500_fg_cap_scaling cap_scale; } ;
struct TYPE_5__ {scalar_t__ charging; } ;
struct ab8500_fg {int /*<<< orphan*/  dev; TYPE_4__* bm; TYPE_2__ bat_cap; TYPE_1__ flags; } ;
struct TYPE_8__ {TYPE_3__* fg_params; } ;
struct TYPE_7__ {int /*<<< orphan*/  maint_thres; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 int max (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ab8500_fg_update_cap_scalers(struct ab8500_fg *di)
{
	struct ab8500_fg_cap_scaling *cs = &di->bat_cap.cap_scale;

	if (!cs->enable)
		return;
	if (di->flags.charging) {
		di->bat_cap.cap_scale.disable_cap_level =
			di->bat_cap.cap_scale.scaled_cap;
		dev_dbg(di->dev, "Cap to stop scale at charge %d%%\n",
				di->bat_cap.cap_scale.disable_cap_level);
	} else {
		if (cs->scaled_cap != 100) {
			cs->cap_to_scale[0] = cs->scaled_cap;
			cs->cap_to_scale[1] = di->bat_cap.prev_percent;
		} else {
			cs->cap_to_scale[0] = 100;
			cs->cap_to_scale[1] =
				max(di->bat_cap.prev_percent,
				    di->bm->fg_params->maint_thres);
		}

		dev_dbg(di->dev, "Cap to scale at discharge %d/%d\n",
				cs->cap_to_scale[0], cs->cap_to_scale[1]);
	}
}