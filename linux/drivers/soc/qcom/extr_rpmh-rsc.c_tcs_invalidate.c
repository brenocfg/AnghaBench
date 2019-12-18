#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tcs_group {int offset; int num_tcs; int /*<<< orphan*/  lock; int /*<<< orphan*/  slots; } ;
struct rsc_drv {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  MAX_TCS_SLOTS ; 
 int /*<<< orphan*/  RSC_DRV_CMD_ENABLE ; 
 int /*<<< orphan*/  RSC_DRV_CMD_WAIT_FOR_CMPL ; 
 scalar_t__ bitmap_empty (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_zero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tcs_group* get_tcs_of_type (struct rsc_drv*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcs_is_free (struct rsc_drv*,int) ; 
 int /*<<< orphan*/  write_tcs_reg_sync (struct rsc_drv*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tcs_invalidate(struct rsc_drv *drv, int type)
{
	int m;
	struct tcs_group *tcs;

	tcs = get_tcs_of_type(drv, type);

	spin_lock(&tcs->lock);
	if (bitmap_empty(tcs->slots, MAX_TCS_SLOTS)) {
		spin_unlock(&tcs->lock);
		return 0;
	}

	for (m = tcs->offset; m < tcs->offset + tcs->num_tcs; m++) {
		if (!tcs_is_free(drv, m)) {
			spin_unlock(&tcs->lock);
			return -EAGAIN;
		}
		write_tcs_reg_sync(drv, RSC_DRV_CMD_ENABLE, m, 0);
		write_tcs_reg_sync(drv, RSC_DRV_CMD_WAIT_FOR_CMPL, m, 0);
	}
	bitmap_zero(tcs->slots, MAX_TCS_SLOTS);
	spin_unlock(&tcs->lock);

	return 0;
}