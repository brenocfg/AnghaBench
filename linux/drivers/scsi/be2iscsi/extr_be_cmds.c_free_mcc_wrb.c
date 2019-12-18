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
struct be_queue_info {int /*<<< orphan*/  used; } ;
struct TYPE_2__ {struct be_queue_info q; } ;
struct be_ctrl_info {unsigned int* mcc_tag; size_t mcc_free_index; int /*<<< orphan*/  mcc_lock; int /*<<< orphan*/  mcc_tag_available; TYPE_1__ mcc_obj; } ;

/* Variables and functions */
 int MAX_MCC_CMD ; 
 unsigned int MCC_Q_CMD_TAG_MASK ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void free_mcc_wrb(struct be_ctrl_info *ctrl, unsigned int tag)
{
	struct be_queue_info *mccq = &ctrl->mcc_obj.q;

	spin_lock(&ctrl->mcc_lock);
	tag = tag & MCC_Q_CMD_TAG_MASK;
	ctrl->mcc_tag[ctrl->mcc_free_index] = tag;
	if (ctrl->mcc_free_index == (MAX_MCC_CMD - 1))
		ctrl->mcc_free_index = 0;
	else
		ctrl->mcc_free_index++;
	ctrl->mcc_tag_available++;
	mccq->used--;
	spin_unlock(&ctrl->mcc_lock);
}