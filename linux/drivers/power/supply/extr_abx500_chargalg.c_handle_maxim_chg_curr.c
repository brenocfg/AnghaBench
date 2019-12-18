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
struct TYPE_4__ {int /*<<< orphan*/  current_iset; } ;
struct abx500_chargalg {int /*<<< orphan*/  dev; TYPE_3__* bm; TYPE_1__ ccm; } ;
typedef  enum maxim_ret { ____Placeholder_maxim_ret } maxim_ret ;
struct TYPE_6__ {size_t batt_id; TYPE_2__* bat_type; } ;
struct TYPE_5__ {int /*<<< orphan*/  normal_cur_lvl; } ;

/* Variables and functions */
#define  MAXIM_RET_CHANGE 130 
#define  MAXIM_RET_IBAT_TOO_HIGH 129 
#define  MAXIM_RET_NOACTION 128 
 int abx500_chargalg_chg_curr_maxim (struct abx500_chargalg*) ; 
 int abx500_chargalg_update_chg_curr (struct abx500_chargalg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void handle_maxim_chg_curr(struct abx500_chargalg *di)
{
	enum maxim_ret ret;
	int result;

	ret = abx500_chargalg_chg_curr_maxim(di);
	switch (ret) {
	case MAXIM_RET_CHANGE:
		result = abx500_chargalg_update_chg_curr(di,
			di->ccm.current_iset);
		if (result)
			dev_err(di->dev, "failed to set chg curr\n");
		break;
	case MAXIM_RET_IBAT_TOO_HIGH:
		result = abx500_chargalg_update_chg_curr(di,
			di->bm->bat_type[di->bm->batt_id].normal_cur_lvl);
		if (result)
			dev_err(di->dev, "failed to set chg curr\n");
		break;

	case MAXIM_RET_NOACTION:
	default:
		/* Do nothing..*/
		break;
	}
}