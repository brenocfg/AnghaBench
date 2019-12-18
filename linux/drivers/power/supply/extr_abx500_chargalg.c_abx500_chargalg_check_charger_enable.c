#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int charger_type; } ;
struct abx500_chargalg {int charge_state; TYPE_5__* bm; TYPE_6__* ac_chg; TYPE_2__ chg_info; TYPE_7__* usb_chg; } ;
struct TYPE_8__ {int (* check_enable ) (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_14__ {TYPE_1__ ops; } ;
struct TYPE_10__ {int (* check_enable ) (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_13__ {TYPE_3__ ops; int /*<<< orphan*/  external; } ;
struct TYPE_12__ {size_t batt_id; TYPE_4__* bat_type; } ;
struct TYPE_11__ {int /*<<< orphan*/  normal_cur_lvl; int /*<<< orphan*/  normal_vol_lvl; } ;

/* Variables and functions */
 int AC_CHG ; 
#define  STATE_MAINTENANCE_A 130 
#define  STATE_MAINTENANCE_B 129 
#define  STATE_NORMAL 128 
 int USB_CHG ; 
 int stub1 (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub2 (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int abx500_chargalg_check_charger_enable(struct abx500_chargalg *di)
{
	switch (di->charge_state) {
	case STATE_NORMAL:
	case STATE_MAINTENANCE_A:
	case STATE_MAINTENANCE_B:
		break;
	default:
		return 0;
	}

	if (di->chg_info.charger_type & USB_CHG) {
		return di->usb_chg->ops.check_enable(di->usb_chg,
                         di->bm->bat_type[di->bm->batt_id].normal_vol_lvl,
                         di->bm->bat_type[di->bm->batt_id].normal_cur_lvl);
	} else if ((di->chg_info.charger_type & AC_CHG) &&
		   !(di->ac_chg->external)) {
		return di->ac_chg->ops.check_enable(di->ac_chg,
                         di->bm->bat_type[di->bm->batt_id].normal_vol_lvl,
                         di->bm->bat_type[di->bm->batt_id].normal_cur_lvl);
	}
	return 0;
}