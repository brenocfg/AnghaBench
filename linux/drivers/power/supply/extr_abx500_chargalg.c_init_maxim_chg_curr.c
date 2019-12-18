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
struct TYPE_8__ {scalar_t__ level; int /*<<< orphan*/  condition_cnt; int /*<<< orphan*/  max_current; int /*<<< orphan*/  test_delta_i; int /*<<< orphan*/  current_iset; int /*<<< orphan*/  original_iset; } ;
struct abx500_chargalg {TYPE_4__ ccm; TYPE_3__* bm; } ;
struct TYPE_7__ {size_t batt_id; TYPE_2__* maxi; TYPE_1__* bat_type; } ;
struct TYPE_6__ {int /*<<< orphan*/  wait_cycles; int /*<<< orphan*/  chg_curr; int /*<<< orphan*/  charger_curr_step; } ;
struct TYPE_5__ {int /*<<< orphan*/  normal_cur_lvl; } ;

/* Variables and functions */

__attribute__((used)) static void init_maxim_chg_curr(struct abx500_chargalg *di)
{
	di->ccm.original_iset =
		di->bm->bat_type[di->bm->batt_id].normal_cur_lvl;
	di->ccm.current_iset =
		di->bm->bat_type[di->bm->batt_id].normal_cur_lvl;
	di->ccm.test_delta_i = di->bm->maxi->charger_curr_step;
	di->ccm.max_current = di->bm->maxi->chg_curr;
	di->ccm.condition_cnt = di->bm->maxi->wait_cycles;
	di->ccm.level = 0;
}