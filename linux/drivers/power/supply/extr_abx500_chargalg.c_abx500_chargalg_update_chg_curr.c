#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int charger_type; int ac_iset; int usb_iset; } ;
struct abx500_chargalg {TYPE_4__* usb_chg; TYPE_2__ chg_info; TYPE_5__* ac_chg; } ;
struct TYPE_6__ {int (* update_curr ) (TYPE_5__*,int) ;} ;
struct TYPE_10__ {TYPE_1__ ops; scalar_t__ max_out_curr; } ;
struct TYPE_8__ {int (* update_curr ) (TYPE_4__*,int) ;} ;
struct TYPE_9__ {TYPE_3__ ops; scalar_t__ max_out_curr; } ;

/* Variables and functions */
 int AC_CHG ; 
 int ENXIO ; 
 int USB_CHG ; 
 int min (int,scalar_t__) ; 
 int stub1 (TYPE_5__*,int) ; 
 int stub2 (TYPE_4__*,int) ; 

__attribute__((used)) static int abx500_chargalg_update_chg_curr(struct abx500_chargalg *di,
		int iset)
{
	/* Check if charger exists and update current if charging */
	if (di->ac_chg && di->ac_chg->ops.update_curr &&
			di->chg_info.charger_type & AC_CHG) {
		/*
		 * Select maximum of what both the charger
		 * and the battery supports
		 */
		if (di->ac_chg->max_out_curr)
			iset = min(iset, di->ac_chg->max_out_curr);

		di->chg_info.ac_iset = iset;

		return di->ac_chg->ops.update_curr(di->ac_chg, iset);
	} else if (di->usb_chg && di->usb_chg->ops.update_curr &&
			di->chg_info.charger_type & USB_CHG) {
		/*
		 * Select maximum of what both the charger
		 * and the battery supports
		 */
		if (di->usb_chg->max_out_curr)
			iset = min(iset, di->usb_chg->max_out_curr);

		di->chg_info.usb_iset = iset;

		return di->usb_chg->ops.update_curr(di->usb_chg, iset);
	}

	return -ENXIO;
}