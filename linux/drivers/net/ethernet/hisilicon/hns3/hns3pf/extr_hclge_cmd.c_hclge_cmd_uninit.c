#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  lock; } ;
struct TYPE_7__ {int /*<<< orphan*/  lock; } ;
struct TYPE_8__ {TYPE_1__ csq; TYPE_2__ crq; } ;
struct TYPE_9__ {TYPE_3__ cmq; } ;
struct hclge_dev {TYPE_4__ hw; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_STATE_CMD_DISABLE ; 
 int /*<<< orphan*/  hclge_cmd_uninit_regs (TYPE_4__*) ; 
 int /*<<< orphan*/  hclge_destroy_cmd_queue (TYPE_4__*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void hclge_cmd_uninit(struct hclge_dev *hdev)
{
	spin_lock_bh(&hdev->hw.cmq.csq.lock);
	spin_lock(&hdev->hw.cmq.crq.lock);
	set_bit(HCLGE_STATE_CMD_DISABLE, &hdev->state);
	hclge_cmd_uninit_regs(&hdev->hw);
	spin_unlock(&hdev->hw.cmq.crq.lock);
	spin_unlock_bh(&hdev->hw.cmq.csq.lock);

	hclge_destroy_cmd_queue(&hdev->hw);
}