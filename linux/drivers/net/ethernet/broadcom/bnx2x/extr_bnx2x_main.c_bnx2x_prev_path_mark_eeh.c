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
struct bnx2x_prev_path_list {int aer; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,int) ; 
 int BP_PATH (struct bnx2x*) ; 
 struct bnx2x_prev_path_list* bnx2x_prev_path_get_entry (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_prev_sem ; 
 int down_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bnx2x_prev_path_mark_eeh(struct bnx2x *bp)
{
	struct bnx2x_prev_path_list *tmp_list;
	int rc;

	rc = down_interruptible(&bnx2x_prev_sem);
	if (rc) {
		BNX2X_ERR("Received %d when tried to take lock\n", rc);
		return rc;
	}

	tmp_list = bnx2x_prev_path_get_entry(bp);
	if (tmp_list) {
		tmp_list->aer = 1;
		rc = 0;
	} else {
		BNX2X_ERR("path %d: Entry does not exist for eeh; Flow occurs before initial insmod is over ?\n",
			  BP_PATH(bp));
	}

	up(&bnx2x_prev_sem);

	return rc;
}