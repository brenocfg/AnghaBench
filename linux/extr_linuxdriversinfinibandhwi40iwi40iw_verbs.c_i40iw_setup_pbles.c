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
typedef  int /*<<< orphan*/  u64 ;
struct i40iw_pble_info {scalar_t__ addr; } ;
struct TYPE_2__ {struct i40iw_pble_info* leaf; } ;
struct i40iw_pble_alloc {int level; TYPE_1__ level2; struct i40iw_pble_info level1; } ;
struct i40iw_pbl {int pbl_allocated; struct i40iw_pble_alloc pble_alloc; } ;
struct i40iw_mr {int /*<<< orphan*/ * pgaddrmem; int /*<<< orphan*/  page_cnt; struct i40iw_pbl iwpbl; } ;
struct i40iw_device {int /*<<< orphan*/  pbl_mutex; int /*<<< orphan*/  pble_rsrc; int /*<<< orphan*/  sc_dev; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;
typedef  enum i40iw_pble_level { ____Placeholder_i40iw_pble_level } i40iw_pble_level ;

/* Variables and functions */
 int ENOMEM ; 
 int I40IW_LEVEL_1 ; 
 int /*<<< orphan*/  i40iw_copy_user_pgaddrs (struct i40iw_mr*,int /*<<< orphan*/ *,int) ; 
 int i40iw_get_pble (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct i40iw_pble_alloc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int i40iw_setup_pbles(struct i40iw_device *iwdev,
			     struct i40iw_mr *iwmr,
			     bool use_pbles)
{
	struct i40iw_pbl *iwpbl = &iwmr->iwpbl;
	struct i40iw_pble_alloc *palloc = &iwpbl->pble_alloc;
	struct i40iw_pble_info *pinfo;
	u64 *pbl;
	enum i40iw_status_code status;
	enum i40iw_pble_level level = I40IW_LEVEL_1;

	if (use_pbles) {
		mutex_lock(&iwdev->pbl_mutex);
		status = i40iw_get_pble(&iwdev->sc_dev, iwdev->pble_rsrc, palloc, iwmr->page_cnt);
		mutex_unlock(&iwdev->pbl_mutex);
		if (status)
			return -ENOMEM;

		iwpbl->pbl_allocated = true;
		level = palloc->level;
		pinfo = (level == I40IW_LEVEL_1) ? &palloc->level1 : palloc->level2.leaf;
		pbl = (u64 *)pinfo->addr;
	} else {
		pbl = iwmr->pgaddrmem;
	}

	i40iw_copy_user_pgaddrs(iwmr, pbl, level);

	if (use_pbles)
		iwmr->pgaddrmem[0] = *pbl;

	return 0;
}