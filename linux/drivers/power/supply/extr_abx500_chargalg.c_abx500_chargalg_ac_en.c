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
struct TYPE_4__ {int ac_iset; int ac_vset; } ;
struct abx500_chargalg {TYPE_3__* ac_chg; int /*<<< orphan*/  dev; TYPE_1__ chg_info; } ;
struct TYPE_5__ {int (* enable ) (TYPE_3__*,int,int,int) ;} ;
struct TYPE_6__ {TYPE_2__ ops; scalar_t__ external; scalar_t__ max_out_curr; scalar_t__ max_out_volt; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  blocking_notifier_call_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  charger_notifier_list ; 
 int min (int,scalar_t__) ; 
 int stub1 (TYPE_3__*,int,int,int) ; 

__attribute__((used)) static int abx500_chargalg_ac_en(struct abx500_chargalg *di, int enable,
	int vset, int iset)
{
	static int abx500_chargalg_ex_ac_enable_toggle;

	if (!di->ac_chg || !di->ac_chg->ops.enable)
		return -ENXIO;

	/* Select maximum of what both the charger and the battery supports */
	if (di->ac_chg->max_out_volt)
		vset = min(vset, di->ac_chg->max_out_volt);
	if (di->ac_chg->max_out_curr)
		iset = min(iset, di->ac_chg->max_out_curr);

	di->chg_info.ac_iset = iset;
	di->chg_info.ac_vset = vset;

	/* Enable external charger */
	if (enable && di->ac_chg->external &&
	    !abx500_chargalg_ex_ac_enable_toggle) {
		blocking_notifier_call_chain(&charger_notifier_list,
					     0, di->dev);
		abx500_chargalg_ex_ac_enable_toggle++;
	}

	return di->ac_chg->ops.enable(di->ac_chg, enable, vset, iset);
}