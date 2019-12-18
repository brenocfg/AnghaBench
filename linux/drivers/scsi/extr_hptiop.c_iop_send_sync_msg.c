#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct hptiop_hba {scalar_t__ msg_done; TYPE_2__* ops; TYPE_1__* host; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* enable_intr ) (struct hptiop_hba*) ;int /*<<< orphan*/  (* iop_intr ) (struct hptiop_hba*) ;int /*<<< orphan*/  (* post_msg ) (struct hptiop_hba*,scalar_t__) ;int /*<<< orphan*/  (* disable_intr ) (struct hptiop_hba*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct hptiop_hba*) ; 
 int /*<<< orphan*/  stub2 (struct hptiop_hba*,scalar_t__) ; 
 int /*<<< orphan*/  stub3 (struct hptiop_hba*) ; 
 int /*<<< orphan*/  stub4 (struct hptiop_hba*) ; 

__attribute__((used)) static int iop_send_sync_msg(struct hptiop_hba *hba, u32 msg, u32 millisec)
{
	u32 i;

	hba->msg_done = 0;
	hba->ops->disable_intr(hba);
	hba->ops->post_msg(hba, msg);

	for (i = 0; i < millisec; i++) {
		spin_lock_irq(hba->host->host_lock);
		hba->ops->iop_intr(hba);
		spin_unlock_irq(hba->host->host_lock);
		if (hba->msg_done)
			break;
		msleep(1);
	}

	hba->ops->enable_intr(hba);
	return hba->msg_done? 0 : -1;
}