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
struct TYPE_8__ {int /*<<< orphan*/  bm; } ;
struct TYPE_7__ {int /*<<< orphan*/  bm; } ;
struct uwb_rsv_move {TYPE_4__ companion_mas; TYPE_3__ final_mas; } ;
struct TYPE_6__ {int /*<<< orphan*/  bm; } ;
struct uwb_rsv {TYPE_2__ mas; struct uwb_rsv_move mv; struct uwb_rc* rc; } ;
struct device {int dummy; } ;
struct TYPE_5__ {struct device dev; } ;
struct uwb_drp_backoff_win {int can_reserve_extra_mases; } ;
struct uwb_rc {TYPE_1__ uwb_dev; struct uwb_drp_backoff_win bow; } ;
struct uwb_mas_bm {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  UWB_NUM_MAS ; 
 scalar_t__ UWB_RSV_ALLOC_FOUND ; 
 int /*<<< orphan*/  UWB_RSV_STATE_O_MOVE_EXPANDING ; 
 int /*<<< orphan*/  bitmap_andnot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  uwb_drp_avail_reserve_pending (struct uwb_rc*,TYPE_4__*) ; 
 scalar_t__ uwb_rsv_find_best_allocation (struct uwb_rsv*,struct uwb_mas_bm*,TYPE_3__*) ; 
 int /*<<< orphan*/  uwb_rsv_set_state (struct uwb_rsv*,int /*<<< orphan*/ ) ; 

int uwb_rsv_try_move(struct uwb_rsv *rsv, struct uwb_mas_bm *available)
{
	struct uwb_rc *rc = rsv->rc;
	struct uwb_drp_backoff_win *bow = &rc->bow;
	struct device *dev = &rc->uwb_dev.dev;
	struct uwb_rsv_move *mv;
	int ret = 0;

	if (bow->can_reserve_extra_mases == false)
		return -EBUSY;

	mv = &rsv->mv;

	if (uwb_rsv_find_best_allocation(rsv, available, &mv->final_mas) == UWB_RSV_ALLOC_FOUND) {

		if (!bitmap_equal(rsv->mas.bm, mv->final_mas.bm, UWB_NUM_MAS)) {
			/* We want to move the reservation */
			bitmap_andnot(mv->companion_mas.bm, mv->final_mas.bm, rsv->mas.bm, UWB_NUM_MAS);
			uwb_drp_avail_reserve_pending(rc, &mv->companion_mas);
			uwb_rsv_set_state(rsv, UWB_RSV_STATE_O_MOVE_EXPANDING);
		}
	} else {
		dev_dbg(dev, "new allocation not found\n");
	}

	return ret;
}